import java.awt.Graphics2D;

public class Baum {

	public static float SHIFT = 0.0f;

	public BaumSegment firstSegment;

	public Baum(Vector pos, float initHeight, int depth){
		System.out.println("Neuer Baum!");

		this.firstSegment = new BaumSegment(pos, new Vector(0, -initHeight));
		this.firstSegment.createSegments(depth);
	}

	public void draw(Graphics2D g){
		this.firstSegment.draw(g);
	}

	public class BaumSegment {

		public Vector pos;
		public Vector vec;
		public BaumSegment left = null;
		public BaumSegment right = null;

		public BaumSegment(BaumSegment vorgaenger, float shift){
			this.pos = new Vector(vorgaenger.pos.x + vorgaenger.vec.x, vorgaenger.pos.y + vorgaenger.vec.y);

			float a = 0.75f;
			this.vec = new Vector(vorgaenger.vec.x * a, vorgaenger.vec.y * a);
			this.vec.rotateBy(shift);
			this.vec.rotateBy(SHIFT);
		}

		public BaumSegment(Vector pos, Vector vec){
			this.pos = pos;
			this.vec = vec;
			this.vec.rotateBy(SHIFT);
		}

		public void createSegments(int i){
			if (i > 0) {
				i -= 1;
				float shift = (float)(Math.PI / 4);

				this.right = new BaumSegment(this, shift);
				this.left = new BaumSegment(this, -shift);

				this.right.createSegments(i);
				this.left.createSegments(i);
			}
		}

		public void draw(Graphics2D g){
			g.drawLine((int) this.pos.x, (int) this.pos.y, (int)(this.pos.x + this.vec.x), (int)(this.pos.y + this.vec.y));
			if (this.left != null && this.right != null) {
				this.left.draw(g);
				this.right.draw(g);
			}
		}
	}
}
