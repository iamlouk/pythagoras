import java.awt.*;
import java.awt.event.*;

public class Programm {

	private Frame mainFrame;
	private Panel controlPanel;

	static int WIDTH = 800;
	static int HEIGHT = 600;

	public Programm(){
		prepareGUI();
	}

	public static void main(String[] args){
		Programm  programm = new Programm();
		programm.show();
	}

	private void prepareGUI(){
		mainFrame = new Frame("Java AWT: Pythagoras tree");
		mainFrame.setSize(WIDTH, HEIGHT);
		mainFrame.setLayout(new GridLayout(1, 1));
		mainFrame.addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent windowEvent){
				System.exit(0);
			}
		});

		controlPanel = new Panel();
		controlPanel.setLayout(new GridLayout(1, 1));

		mainFrame.add(controlPanel);
		mainFrame.setVisible(true);

		controlPanel.add(new MyCanvas());
	}

	public void show(){
		mainFrame.setVisible(true);
	}

	class MyCanvas extends Canvas {
		private static final long serialVersionUID = 1L;

		public MyCanvas() {
			setBackground (Color.WHITE);
			setSize(WIDTH, HEIGHT);
		}

		public void paint(Graphics g) {
			Graphics2D g2 = (Graphics2D) g;

			// drawCircle(g2);
			drawBaum(g2);
		}

		public void drawBaum(Graphics2D graphics){
			Vector pos = new Vector(Programm.WIDTH / 2, Programm.HEIGHT);
			Baum b = new Baum(pos, 150, 16);

			b.draw(graphics);
		}

		public void drawCircle(Graphics2D graphics) {
			Vector center = new Vector(Programm.WIDTH / 2, Programm.HEIGHT / 2);
			Vector vec1 = new Vector(0, Programm.WIDTH / 3);
			Vector vec2 = new Vector(0, Programm.WIDTH / 8);
			Vector pos = new Vector(center.x + vec1.x + vec2.x, center.y + vec1.y + vec2.y);

			float rotationPerStep = (float) (Math.PI * 2) / 1000;
			float rotation = 0;
			while (rotation < Math.PI * 2) {
				vec1.rotateBy(rotationPerStep);
				vec2.rotateBy(rotationPerStep * 20);
				rotation += rotationPerStep;

				Vector nextPos =  new Vector(center.x + vec1.x + vec2.x, center.y + vec1.y + vec2.y);

				graphics.drawLine((int) pos.x, (int) pos.y, (int) nextPos.x, (int) nextPos.y);

				pos = nextPos;
			}
		}
	}
}
