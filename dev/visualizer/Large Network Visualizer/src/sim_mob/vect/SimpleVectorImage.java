package sim_mob.vect;

import java.awt.*;
import java.awt.geom.AffineTransform;
import java.awt.image.BufferedImage;
import java.io.BufferedReader;

import com.google.gson.Gson;

public class SimpleVectorImage {
	//No-argument constructor; required for gson
	private SimpleVectorImage() {
		for (int i=0; i<rotatedBuffers.length; i++) {
			rotatedBuffers[i] = new CachedBuffer();
		}
	}
	
	private CoordinateSystem coordinates;
	
	private IndexedColor[] colors;
	
	private VectorItem[] drawOrder;
	
	//Cached buffers
	class CachedBuffer {
		double scaleAmt;
		BufferedImage img;
	}
	private CachedBuffer[] rotatedBuffers = new CachedBuffer[360];
	
	//Helper
	private static Gson gson = new Gson();
	
	//Load from file
	public static SimpleVectorImage LoadFromFile(BufferedReader file) {
		return gson.fromJson(file, SimpleVectorImage.class);
	}
	
	//Retrieve a scaled, rotated version of this image.
	public BufferedImage getImage(double scaleFactor, int rotateAngle) {
		//Bound, retrieve
		CachedBuffer cacheEntry = rotatedBuffers[rotateAngle%360];
		
		//Do we need to refresh the image cache?
		if (cacheEntry.img==null || Math.abs(scaleFactor-cacheEntry.scaleAmt)>1E-7) { //Just hard-code an epsilon value for now.
			cacheEntry.scaleAmt = scaleFactor;
			redrawAtScale(cacheEntry, rotateAngle);
		}
		
		return cacheEntry.img;
	}
	
	//Redraw all 360 degree rotations of this image at this scale.
	private void redrawAtScale(CachedBuffer entry, int angle) {
		//Make a new image to hold this.
		//TODO: Currently, we use a buffer 100x100 in size. This should _definitely_ scale with the Image in 
		//      question, but for now I'm just testing out centering.
		entry.img = new BufferedImage(100, 100, BufferedImage.TYPE_INT_ARGB);
		Graphics2D g = (Graphics2D)entry.img.getGraphics();
		g.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
		
		//TEMP: For debugging
		g.setBackground(Color.white);
		g.clearRect(0, 0, entry.img.getWidth(), entry.img.getHeight());
		
		//Create a transformation for this angle/scale. Translate to the center of the image.
		AffineTransform at = AffineTransform.getTranslateInstance(entry.img.getWidth()/2, entry.img.getHeight()/2);
		at.scale(entry.scaleAmt, entry.scaleAmt);
		at.rotate((Math.PI*angle)/180);
		g.setTransform(at);
		
		//Now draw it.
		draw(g);
	}
	
	//Draw a single instance.
	private void draw(Graphics2D g) {
		//Amount to subtract from each component to get a centered version.
		float[] off = new float[]{(int)Math.ceil(coordinates.getWidth()/2.0), (int)Math.ceil(coordinates.getHeight()/2.0)};
		
		//Draw each VectorItem
		for (VectorItem item : drawOrder) {
			//Draw the background.
			if (!item.getShape().equals("line")) {
				if (item.getBkgrd()!=null) {
					g.setColor(getColor(item.getBkgrd()));
				} else if (item.getGradient()!=null) {
					//TODO: Gradients
					g.setColor(getColor(item.getGradient()[0]));
				} else {
					throw new RuntimeException("No background or gradient for item.");
				}
				fillPoints(g, item.getShape(), item.getPoints(), off);
			}
			
			//Draw the stroke
			g.setColor(getColor(item.getStroke()));
			g.setStroke(new BasicStroke(item.getWidth()));
			drawPoints(g, item.getShape(), item.getPoints(), off);
		}
	}
	
	//TEMP: Draw a shape
	private void fillPoints(Graphics2D g, String shapeType, float[] points, float[] off) {
		if (shapeType.equals("poly")) {
			int[] xPoints = new int[points.length/2];
			int[] yPoints = new int[points.length/2];
			splitToPlanarArrays(points, off, xPoints, yPoints);
			g.fillPolygon(xPoints, yPoints, xPoints.length);
		} else {
			throw new RuntimeException("Unknown shape: " + shapeType);
		}
	}
	
	//TEMP: Draw a shape
	private void drawPoints(Graphics2D g, String shapeType, float[] points, float[] off) {
		if (shapeType.equals("poly")) {
			int[] xPoints = new int[points.length/2];
			int[] yPoints = new int[points.length/2];
			splitToPlanarArrays(points, off, xPoints, yPoints);
			g.drawPolygon(xPoints, yPoints, xPoints.length);
		} else if (shapeType.equals("line")) {
			if (points.length!=4) {
				throw new RuntimeException("Points array must contain four items for a line.");
			}
			g.drawLine((int)(points[0]-off[0]), (int)(points[1]-off[1]), (int)(points[2]-off[0]), (int)(points[3]-off[1]));
		} else {
			throw new RuntimeException("Unknown shape: " + shapeType);
		}
	}
	
	//TEMP
	private void splitToPlanarArrays(float[] orig, float[] off, int[] plane1, int[] plane2) {
		if (orig.length%2!=0) {
			throw new RuntimeException("Can't split array into planes; its size is not even.");
		}
		for (int i=0; i<orig.length/2; i++) {
			plane1[i] = (int)(orig[i*2]-off[0]);
			plane2[i] = (int)(orig[i*2 +1]-off[1]);
		}
	}
	
	//TEMP: Inefficient.
	private Color getColor(String key) {
		for (IndexedColor clr : colors) {
			if (clr.getId().equals(key)) {
				String rgb = clr.getRGB();
				if (rgb==null) {
					throw new RuntimeException("Can't draw color, is null: " + key);
				}
				return new Color(Integer.parseInt(rgb, 0x10));
			}
		}
		throw new RuntimeException("Invalid color: " + key);
	}
}

