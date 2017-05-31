extern crate sdl2;

use sdl2::rect::Point;

pub struct Vector {
	x: f32,
	y: f32,
}

impl Vector {
	pub fn new(x: f32, y: f32) -> Vector {
		return Vector { x: x, y: y };
	}

	pub fn length(&self) -> f32 {
		return ((self.x * self.x) + (self.y * self.y)).sqrt();
	}

	pub fn to_length(&mut self, len: f32) {
		let cl = self.length();
		self.x = (self.x / cl) * len;
		self.y = (self.y / cl) * len;
	}

	pub fn rotate(&mut self, angle: f32) {
		let sin = angle.sin();
		let cos = angle.cos();

		let x = (self.x * cos) - (self.y * sin);
		let y = (self.x * sin) + (self.y * cos);

		self.x = x;
		self.y = y;
	}

	pub fn as_point(&self) -> Point {
		return Point::new(self.x as i32, self.y as i32);
	}
}

#[allow(non_snake_case)]
pub struct Square {
	A: Vector,
	B: Vector,
	C: Vector,
	D: Vector,

	vec1: Vector,
	vec2: Vector,

	P: Vector
}

impl Square {

	#[allow(non_snake_case)]
	pub fn new(A: Vector, vec1: Vector, vec2: Vector, shift: f32) -> Square {
		let B = Vector::new(A.x + vec1.x, A.y + vec1.y);
		let C = Vector::new(B.x + vec2.x, B.y + vec2.y);
		let D = Vector::new(A.x + vec2.x, A.y + vec2.y);

		let mut vec = Vector::new(vec1.x / 2f32, vec1.y / 2f32);
		vec.rotate(shift);

		let P = Vector::new(B.x + (vec2.x / 2f32) + vec.x, B.y + (vec2.y / 2f32) + vec.y);
		return Square {
			A: A, B: B,
			C: C, D: D,

			vec1: vec1,
			vec2: vec2,

			P: P
		};
	}

	pub fn draw(&self, renderer: &mut sdl2::render::Renderer) {
		renderer.draw_line(self.A.as_point(), self.B.as_point()).unwrap();
		renderer.draw_line(self.B.as_point(), self.C.as_point()).unwrap();
		renderer.draw_line(self.C.as_point(), self.D.as_point()).unwrap();
		renderer.draw_line(self.D.as_point(), self.A.as_point()).unwrap();
	}

	pub fn recalc_p(&mut self, shift: f32) {
		let point = Vector::new(self.B.x + (self.vec2.x / 2f32), self.B.y + (self.vec2.y / 2f32));

		let mut vec = Vector::new(self.vec1.x / 2f32, self.vec1.y / 2f32);
		vec.rotate(shift);

		self.P.x = point.x + vec.x;
		self.P.y = point.y + vec.y;
	}

	pub fn next_left(&self, shift: f32) -> Square {
		let mut vec1 = Vector::new(self.P.x - self.C.x, self.P.y - self.C.y);
		let vec2 = Vector::new(self.P.x - self.B.x, self.P.y - self.B.y);

		vec1.to_length( vec2.length() );

		return Square::new(Vector::new(self.B.x, self.B.y), vec1, vec2, shift);
	}

	pub fn next_right(&self, shift: f32) -> Square {
		let mut vec1 = Vector::new(self.P.x - self.B.x, self.P.y - self.B.y);
		let vec2 = Vector::new(self.C.x - self.P.x, self.C.y - self.P.y);

		vec1.to_length( vec2.length() );

		return Square::new(Vector::new(self.P.x, self.P.y), vec1, vec2, shift);
	}
}
