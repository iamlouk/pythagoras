public class Vector {
	public float x = 0;
	public float y = 0;

	public Vector(float x, float y){
		this.x = x;
		this.y = y;
	}

	public void rotateBy(float alpha){
		float cos = (float) Math.cos(alpha);
		float sin = (float) Math.sin(alpha);
		float x = this.x * cos - this.y * sin;
		float y = this.x * sin + this.y * cos;
		this.x = x;
		this.y = y;
	}

	public float length(){
		return (float) Math.sqrt(x*x + y*y);
	}
}
