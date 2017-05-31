class Vector {
	constructor(x, y) {
		this.x = x;
		this.y = y;
	}

	get length(){
		return Math.sqrt(this.x * this.x + this.y * this.y);
	}

	rotateByAngle(a){
		let cos = Math.cos(a);
		let sin = Math.sin(a);
		let x = this.x * cos - this.y * sin;
		let y = this.x * sin + this.y * cos;
		this.x = x;
		this.y = y;
	}
}

const Geo = ({

	getNext: function(prevPos, prevVec){
		let p = new Vector(prevPos.x + prevVec.x, prevPos.y + prevVec.y);

		let vec_x = prevVec.x * 0.75;
		let vec_y = prevVec.y * 0.75;

		let vecL = new Vector(vec_x, vec_y);

		vecL.rotateByAngle(Math.PI / 4);

		let vecR = new Vector(vec_x, vec_y);
		vecR.rotateByAngle(-(Math.PI / 4));

		return {
			pos: p,
			vecL: vecL,
			vecR: vecR
		};
	}

});
