extern crate sdl2;

use sdl2::event::Event;
use sdl2::keyboard::Keycode;
use sdl2::pixels::Color;

use std::time::{Duration, SystemTime};
use std::io::prelude::*;

static WINDOW_WIDTH:u32 = 1000;
static WINDOW_HEIGHT:u32 = 650;
static MS_PER_FRAME:u64 = (1000 / 60);

mod geometry;
use geometry::*;

fn draw_pythagoras_tree(prev_rect: &Square, counter: i8, shift: f32, renderer: &mut sdl2::render::Renderer) {
	let left = prev_rect.next_left(shift);
	let right = prev_rect.next_right(shift);

	left.draw(renderer);
	right.draw(renderer);

	if counter > 0 {
		draw_pythagoras_tree(&left,  counter - 1, shift, renderer);
		draw_pythagoras_tree(&right, counter - 1, shift, renderer);
	}
}

fn main() {
	println!("Hallo, Rust!");

	let sdl_context = sdl2::init().unwrap();
	let video_subsystem = sdl_context.video().unwrap();
	let window = video_subsystem.window("Pythagoras: Hallo, Welt!", WINDOW_WIDTH, WINDOW_HEIGHT)
		.position_centered()
		.opengl()
		.build()
		.unwrap();

	let mut renderer = window.renderer()
		.build()
		.unwrap();

	renderer.set_draw_color( Color::RGB(255, 255, 255) );
	renderer.clear();

	let rect_width = (WINDOW_WIDTH as f32) * 0.15;
	let mut first_rect = Square::new(
		Vector::new(((WINDOW_WIDTH / 2) - (rect_width as u32 / 2)) as f32, WINDOW_HEIGHT as f32),
		Vector::new(0f32, -rect_width),
		Vector::new(rect_width, 0f32),
		0.0
	);

	let mut shift:f32 = 0.0;
	let mut i:u64 = 0;
	let mut average_ms_per_frame:u64 = 0;
	let mut event_pump = sdl_context.event_pump().unwrap();

	print!("FPS: ??\r");
	'mainloop: loop {
		let now = SystemTime::now();
		for event in event_pump.poll_iter() {
			match event {
				Event::Quit {..} | Event::KeyDown { keycode: Some(Keycode::Escape), .. } => {
					break 'mainloop
				},
				_ => {}
			}
		}

		renderer.set_draw_color( Color::RGB(255, 255, 255) );
		renderer.clear();

		renderer.set_draw_color(Color::RGB(0, 0, 0));
		first_rect.draw(&mut renderer);
		draw_pythagoras_tree(&first_rect, 11, shift, &mut renderer);
		renderer.present();

		i += 1;

		shift = (i as f32 * 0.01).sin() * 0.1;

		first_rect.recalc_p(shift);

		let elapsed_time: Duration = now.elapsed().unwrap();
		let mut ms = (1000*1000*1000 * elapsed_time.as_secs() + (elapsed_time.subsec_nanos() as u64))/(1000 * 1000);

		if ms < MS_PER_FRAME {
			let correction = MS_PER_FRAME - ms;
			std::thread::sleep( Duration::from_millis( correction ) );
			ms += correction;
		}

		average_ms_per_frame = (average_ms_per_frame + ms) / 2;

		if (i % 25) == 0 {
			print!("FPS: {:?}\r", 1000 / average_ms_per_frame);
			std::io::stdout().flush().ok().expect("could not flush stdout");
		}
	}

	println!("\nBye!    ");
}
