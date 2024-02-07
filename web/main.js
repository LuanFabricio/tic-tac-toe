// Credits: https://github.com/tsoding/raylib.js/blob/main/raylib.js
function make_environment(...envs) {
	return new Proxy(envs, {
		get(target, prop, receiver) {
			for (let env of envs) {
				if (env.hasOwnProperty(prop)) {
					return env[prop];
				}
			}
			return (...args) => {console.error("NOT IMPLEMENTED: "+prop, args)}
		}
	});
}

/**
* @param {KeyboardEvent} key 
* */
function keyToCode(key) {
	const keyMapping = {
		"Enter": 257,
	};
	
	let code = keyMapping[key.code];
	if (code) {
		return code;
	}

	return key.key.charCodeAt();
}

class Game {
	constructor() {
		this.reset();
	}

	/** @private */
	reset() {
		/** 
		* @private 
		* @type {number[]}
		* */
		this.mouse_pos = [0, 0];
		/** 
		* @private 
		* @type {CanvasRenderingContext2D | undefined}
		* */
		this.ctx = undefined;
		/** 
		* @private 
		* @type {Number | undefined}
		* */
		this.dt = undefined;
		/** 
		* @private 
		* @type {Number | undefined}
		* */
		this.previous = undefined;
		/** @private */
		this.game_loop = undefined;
		/** @private */
		this.wasm = undefined;
		/** @private */
		this.keys = new Set();
	}

	async init() {

		const canvasId = "game";
		const canvas = document.getElementById(canvasId);
		this.ctx = canvas.getContext("2d");

		const getKeyDown = (key) => {
			this.keys.add(keyToCode(key));
		};
		window.addEventListener("keydown", getKeyDown);

		/** @param {MouseEvent} mouse */
		const mouseMove = (mouse) => {
			const canvas_rect = this.ctx.canvas.getBoundingClientRect();
			const mouse_x = mouse.clientX - canvas_rect.left;
			const mouse_y = mouse.clientY - canvas_rect.top;

			this.mouse_pos = [mouse_x, mouse_y];
		};
		this.ctx.canvas.addEventListener("mousemove", mouseMove);

		/** @type {WebAssembly.WebAssemblyInstantiatedSource} */
		this.wasm = await WebAssembly.instantiateStreaming(
			fetch("./main.wasm"),
			{
				env: make_environment({
					some_cool_function: () => {
						return 42;
					},
					init_window: (width, height, title) => {
						this.ctx.canvas.width = width;
						this.ctx.canvas.height = height;
						const buffer = this.wasm.instance.exports.memory.buffer;	
						document.title = cstr_by_ptr(buffer, title);
					},
					draw_rectangle: (x, y, width, height, color) => {
						this.ctx.fillStyle = color_to_hex(color);
						this.ctx.fillRect(x, y, width, height);
					},
					draw_line: (x0, y0, x1, y1, color) => {
						this.ctx.fillStyle = color_to_hex(color);
						this.ctx.beginPath();
						this.ctx.moveTo(x0, y0);
						this.ctx.lineTo(x1, y1);
						this.ctx.stroke();
					},
					clear_window: (color) => {
						const { width, height } = this.ctx.canvas;
						this.ctx.fillStyle = color_to_hex(color);
						this.ctx.clearRect(0, 0, width, height);
					},
					get_delta_time: () => {
					        return this.dt;
					},
					begin_draw: () => {},
					end_draw: () => {
						this.keys.clear();
					},
					is_key_pressed: (key_code) => {
						return this.keys.has(key_code);
					},
					set_game_loop_func: (func) => {
						this.game_loop = this.wasm.instance.exports.__indirect_function_table.get(func);
					},
					get_mouse_pos: () => {
						let x_offset = window.innerWidth - this.ctx.canvas.width;
						let y_offset = window.innerHeight - this.ctx.canvas.height;
						let x = this.mouse_pos[0] - x_offset;
						let y = this.mouse_pos[1] - y_offset;

						console.log(this.mouse_pos[0], this.mouse_pos[1]);
						console.log(x, y);
						return [400, 300];
					},
					get_mouse_pos_x: () => this.mouse_pos[0],
					get_mouse_pos_y: () => this.mouse_pos[1],
				}),
			}
		);
		console.log(this.wasm);
	}

	run() {
		console.log(this.wasm);
		if (!this.wasm) {
			console.error("Wasm not initialized, please run .init().");
			return;
		}

		this.wasm.instance.exports.main();

		const next = (timestamp) => {
			this.dt = (timestamp - this.previous) / 1000.0;
			this.previous = timestamp;

			this.game_loop();
			window.requestAnimationFrame(next);
		};
		window.requestAnimationFrame((timestamp) => {
			this.previous = timestamp;
			window.requestAnimationFrame(next);
		});
	}
}

const game = new Game();
game.init().then(() => {
	game.run();
});

/** 
* @param {any} buffer 
* @param {string} str 
* */
function cstr_len(mem, str) {
	let len = 0;
	while (mem[str] != 0) {
		len++;
		str++;
	}
	return len;
}

/** 
* @param {ArrayBuffer} buffer 
* @param {str} number 
* */
function cstr_by_ptr(buffer, str) {
	const mem = new Uint8Array(buffer);
	const len = cstr_len(mem, str);
	const str_bytes = new Uint8Array(buffer, str, len);
	
	return new TextDecoder().decode(str_bytes);
}

/**
* @param {Number} color
* */
function color_to_hex(color) {
	const r = ((color>>(8*0))&0xff).toString(16).padStart(2, '0');
	const g = ((color>>(8*1))&0xff).toString(16).padStart(2, '0');
	const b = ((color>>(8*2))&0xff).toString(16).padStart(2, '0');
	const a = ((color>>(8*3))&0xff).toString(16).padStart(2, '0');

	return '#'+r+g+b+a;
}
