package sim_mob.vis;


import java.awt.*;


import java.awt.event.*;
import java.awt.image.BufferedImage;

import javax.swing.*;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

import com.xuggle.mediatool.*;
import com.xuggle.xuggler.*;

import java.lang.reflect.Field;
import java.io.*;
import java.util.Arrays;
import java.util.HashSet;
import java.util.Hashtable;
import java.util.concurrent.TimeUnit;
import java.util.regex.*;

import sim_mob.conf.CSS_Interface;
import sim_mob.vis.controls.*;
import sim_mob.vis.network.RoadNetwork;
import sim_mob.vis.network.basic.ScaledPoint;
import sim_mob.vis.simultion.SimulationResults;
import sim_mob.vis.util.StringSetter;
import sim_mob.vis.util.Utility;


/**
 * \author Seth N. Hetu
 * \author Zhang Shuai
 */
public class MainFrame extends JFrame {
	public static final long serialVersionUID = 1L;
	//For JComboBox
	private static final String clockRateList[] = {"default-50ms","10 ms", "50 ms", "100 ms", "200 ms","500 ms","1000 ms"};
    	
	//Regex
	private static final String num = "([0-9]+)";
	public static final Pattern NUM_REGEX = Pattern.compile(num);
	
	//Center (main) panel
	private NetworkPanel newViewPnl;
	private SimulationResults simData;
	private JTextField console;
	
	//LHS panel
	private JProgressBar drawnPercent; //How many items are drawn.
	private JButton openLogFile;
	private JButton openEmbeddedFile;
	private JButton showFakeAgent;
	private JButton zoomIn;
	private JButton	zoomOut;
	private JButton debug;
	
    private JComboBox clockRateComboBox;
    private ImageIcon debugIcon;
    private ImageIcon displayIcon;
    
    private JComboBox imgScaleBox;
    
    private JComboBox trackAgentIDs;
    private JButton renderVideo;
    private JButton squareViewport;
    
    private JButton annotationLevel;
    private int currAnnotLevel; //0,1,2,3 (simple progression; migrate to an enum if you add more)
    private ImageIcon alvl_None;
    private ImageIcon alvl_Aimsun;
    private ImageIcon alvl_Mitsim;
    private ImageIcon alvl_Both;
    
    private JButton graphToShow;
    private int currGraphShown;
    private ImageIcon graphVis_None;
    private ImageIcon graphVis_Driver;
    private ImageIcon graphVis_Ped;    
    
	
	//Lower panel
	private Timer animTimer;
	private JSlider frameTickSlider;
	private JButton revBtn;
	private JButton playBtn;
	private JButton fwdBtn;
	private ImageIcon playIcon;
	private ImageIcon pauseIcon;
	
	
	//Helper
	public static CSS_Interface Config;
	private boolean showFake;
	private boolean showDebugMode;
	
	//Helper class
	private class StringItem {
		private String name;
		private int value;
		public StringItem(String name, int value) {
			this.name = name;
			this.value = value;
		}
		public String toString() {
			return name;
		}
		public int getValue() {
			return value;
		}
	}
	
		
	/**
	 * NOTE: Currently, I haven't found a good way to switch between MainFrame as a JFrame and MainFrame as an Applet.
	 *       Basically, it requires changing 4 lines of code.
	 */
	public MainFrame(CSS_Interface config) {
		//Initial setup: FRAME
		super("Sim Mobility Visualization");

		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setLocation(150, 100);
		MainFrame.Config = config;
		//Initial setup: FRAME AND APPLET
		this.setSize(1024, 768);
		this.showFake = false;
		this.showDebugMode = false;
		//Components and layout
		try {
			loadComponents();
			createListeners();
			addComponents(this.getContentPane());
			//pack(); //Layout's making this hard...
		} catch (Exception ex) {
			throw new RuntimeException(ex);
		}
	}
	
	
	public static Hashtable<String, Color> GetOverrides(String prefix, String[] bkgrdColors, String[] lineColors) {
		Hashtable<String, Color> overrides = new Hashtable<String, Color>();
		for (String id : bkgrdColors) {
			Color clr = MainFrame.Config.getBackground(prefix+"-"+id);
			if (clr!=null) {
				overrides.put(id, clr);
			}
		}
		for (String id : lineColors) {
			Color clr = MainFrame.Config.getLineColor(prefix+"-"+id);
			if (clr!=null) {
				overrides.put(id, clr);
			}
		}
		return overrides;
	}
	
	
	/**
	 * Load all components and initialize them properly.
	 */
	private void loadComponents() throws IOException {
		playIcon = new ImageIcon(Utility.LoadImgResource("res/icons/play.png"));
		pauseIcon = new ImageIcon(Utility.LoadImgResource("res/icons/pause.png"));
		displayIcon = new ImageIcon(Utility.LoadImgResource("res/icons/display.png"));
		debugIcon = new ImageIcon(Utility.LoadImgResource("res/icons/bug.png"));
		
		console = new JTextField();
	    clockRateComboBox = new JComboBox(clockRateList);
	    trackAgentIDs = new JComboBox(new String[]{"", ""});
	    resetTrackAgentIDs(null);
	    
	    imgScaleBox = new JComboBox(new String[] {"1x scale", "2x scale", "3x scale", "4x scale", "5x scale", "6x scale", "7x scale", "8x scale", "9x scale", "10x scale"});
	    
	    renderVideo = new JButton("Render Video");
	    
	    //Disable our render button if this clearly won't work.
	    renderVideo.setEnabled(false);
	    String osName = System.getProperty("os.name").toLowerCase();
	    if (osName.indexOf("nix")>=0 || osName.indexOf("nux")>=0) {
	    	try {
	    		//If their path is all set...
	    		loadXuggler();
	    	} catch (Throwable t) {
	    		try {
	    			//Mangle the path for them.
	    			hotlinkXuggler();
	    			loadXuggler();
	    		} catch (Throwable t2) {
	    			System.out.println("Couldn't find/load xuggler; video rendering disabled.");
	    			System.out.println("  => " + t2.getMessage());
	    		}
	    	}
	    }
	    
	    squareViewport = new JButton("Square viewport");
	    
	    alvl_None = new ImageIcon(Utility.LoadImgResource("res/icons/annot_none.png"));
	    alvl_Mitsim = new ImageIcon(Utility.LoadImgResource("res/icons/annot_mitsim.png"));
	    alvl_Aimsun = new ImageIcon(Utility.LoadImgResource("res/icons/annot_aimsun.png"));
	    alvl_Both = new ImageIcon(Utility.LoadImgResource("res/icons/annot_both.png"));
	    annotationLevel = new JButton("No annotations");
	    currAnnotLevel = 0;
	    annotationLevel.setIcon(alvl_None);
	    
	    graphVis_None = new ImageIcon(Utility.LoadImgResource("res/icons/sdgraph_none.png"));
	    graphVis_Driver = new ImageIcon(Utility.LoadImgResource("res/icons/sdgraph_driver.png"));
	    graphVis_Ped = new ImageIcon(Utility.LoadImgResource("res/icons/sdgraph_pedestrian.png"));
	    graphToShow = new JButton("Hide graphs");
	    currGraphShown = 0;
	    graphToShow.setIcon(graphVis_None);

	    
	    drawnPercent = new JProgressBar();
	    drawnPercent.setStringPainted(false);
	    openLogFile = new JButton("Open File From...", new ImageIcon(Utility.LoadImgResource("res/icons/open.png")));
		openEmbeddedFile = new JButton("Open Default File", new ImageIcon(Utility.LoadImgResource("res/icons/embed.png")));
		showFakeAgent = new JButton("Show Proxy Agent", new ImageIcon(Utility.LoadImgResource("res/icons/fake.png")));
		zoomIn = new JButton("       Zoom In 	        ", new ImageIcon(Utility.LoadImgResource("res/icons/zoom_in.png")));
		zoomOut = new JButton("      Zoom Out  	    ", new ImageIcon(Utility.LoadImgResource("res/icons/zoom_out.png")));
		debug = new JButton("    Display Mode    ", displayIcon);
		
		frameTickSlider = new JSlider(JSlider.HORIZONTAL);
		revBtn = new JButton(new ImageIcon(Utility.LoadImgResource("res/icons/rev.png")));
		playBtn = new JButton(playIcon);
		fwdBtn = new JButton(new ImageIcon(Utility.LoadImgResource("res/icons/fwd.png")));
		
		newViewPnl = new NetworkPanel(new StringSetter() {
			public void set(String str) {
				//Update the status bar
				String oldValue = console.getText();
				if(oldValue.isEmpty()) {
					console.setText(str);
				} else {
					console.setText(oldValue+"\t"+str);
				}
			}
		});
	}
	
	/**
	 * Add all components to the frame.
	 * @param cp Content Pane of the current Frame.
	 */
	private void addComponents(Container cp) {
		//Left panel
		GridLayout gl = new GridLayout(0,1,0,2);
		JPanel jpLeft = new JPanel(gl);
		jpLeft.add(drawnPercent);
		jpLeft.add(openLogFile);
		jpLeft.add(openEmbeddedFile);
		jpLeft.add(showFakeAgent);
		jpLeft.add(zoomIn);
		jpLeft.add(zoomOut);
		jpLeft.add(debug);
		jpLeft.add(clockRateComboBox);
		jpLeft.add(trackAgentIDs);
		jpLeft.add(imgScaleBox);
		jpLeft.add(renderVideo);
		jpLeft.add(squareViewport);
		jpLeft.add(annotationLevel);
		jpLeft.add(graphToShow);
		
		//Bottom panel
		JPanel jpLower = new JPanel(new BorderLayout());
		jpLower.add(BorderLayout.NORTH, frameTickSlider);
		JPanel jpLower2 = new JPanel(new GridLayout(1, 0, 10, 0));
		jpLower2.add(revBtn);
		jpLower2.add(playBtn);
		jpLower2.add(fwdBtn);
		jpLower.add(BorderLayout.CENTER, jpLower2);
		
		//Main Frame uses a grid bag layout
		GridBagConstraints gbc;
		cp.setLayout(new GridBagLayout());
		
		//Add to the main controller: left panel
		gbc = new GridBagConstraints();
		gbc.gridx = 0;
		gbc.gridy = 0;
		gbc.gridwidth = 1;
		gbc.gridheight = GridBagConstraints.REMAINDER;
		gbc.weightx = 0.1;
		gbc.weighty = 0.1;
		gbc.anchor = GridBagConstraints.PAGE_START;
		gbc.insets = new Insets(10, 5, 10, 5);
		cp.add(jpLeft, gbc);
		
		//Add (and stretch) the console
		gbc = new GridBagConstraints();
		gbc.gridx = 1;
		gbc.gridy = 0;
		gbc.weightx = 0.1;
		gbc.weighty = 0.1;
		gbc.fill = GridBagConstraints.HORIZONTAL;
		cp.add(console, gbc);
		
		//Add to the main controller: center panel
		gbc = new GridBagConstraints();
		gbc.gridx = 1;
		gbc.gridy = 1;
		gbc.ipadx = 800;
		gbc.ipady = 600;
		gbc.weightx = 0.9;
		gbc.weighty = 0.9;
		gbc.fill = GridBagConstraints.BOTH;
		cp.add(newViewPnl, gbc);
		
		//Add to the main controller: right panel
		gbc = new GridBagConstraints();
		gbc.gridx = 1;
		gbc.gridy = 2;
		gbc.weightx = 0.1;
		gbc.weighty = 0.1;
		gbc.anchor = GridBagConstraints.PAGE_END;
		cp.add(jpLower, gbc);
	}
	
	/**
	 * Create all Listeners and hook them up to callback functions.
	 */
	private void createListeners() {
		//Frame tick slider
		frameTickSlider.addChangeListener(new ChangeListener() {
			public void stateChanged(ChangeEvent arg0) {
				if (simData==null) {
					return;
				}
				if (frameTickSlider.isEnabled()) {
					newViewPnl.jumpAnim(frameTickSlider.getValue(), frameTickSlider);
				}
			}
		});
		
		//Play/pause
		playBtn.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				//Anything to play?
				if (simData==null) {
					return;
				}
				
				if (!animTimer.isRunning()) {
					animTimer.start();
					playBtn.setIcon(pauseIcon);
				} else {
					animTimer.stop();
					playBtn.setIcon(playIcon);
				}
			}
		});
		
		//Forward and Backward Button
		fwdBtn.addActionListener(new ActionListener(){
			
			public void actionPerformed(ActionEvent arg0) {
				if (newViewPnl.advanceAnimbyStep(1, frameTickSlider)) {
					animTimer.stop();
					playBtn.setIcon(playIcon);
					return;
				}
				
			}
			
		});

		revBtn.addActionListener(new ActionListener(){
			
			public void actionPerformed(ActionEvent arg0) {
				if (newViewPnl.advanceAnimbyStep(-1, frameTickSlider)) {
					animTimer.stop();
					playBtn.setIcon(playIcon);
					return;
				}
				
			}
			
		});

		//20 FPS, update anim
		animTimer = new Timer(50, new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				if (!newViewPnl.advanceAnim(1, frameTickSlider)) {
					animTimer.stop();
					playBtn.setIcon(playIcon);
					return;
				}
			}
		});
		
		clockRateComboBox.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				
				String speed = (String) clockRateComboBox.getSelectedItem();
				if(!speed.contains("default")){
					String [] items = speed.split(" ");
					
					int clockRate = Integer.parseInt(items[0]);
					
					animTimer.stop();
					
					animTimer = new Timer(clockRate, new ActionListener() {
						public void actionPerformed(ActionEvent arg0) {
							if (!newViewPnl.advanceAnim(1, frameTickSlider)) {
								animTimer.stop();
								playBtn.setIcon(playIcon);
								return;
							}
						}
					});
					animTimer.start();
				}
			}
		});
		
		imgScaleBox.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				newViewPnl.setScaleMultiplier(imgScaleBox.getSelectedIndex()+1);
			}
		});
		
		
		trackAgentIDs.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				if (trackAgentIDs.getSelectedIndex()==-1) {
					return;
				}
					
				newViewPnl.setHighlightID(((StringItem)trackAgentIDs.getSelectedItem()).getValue());
			}
		});
		
		showFakeAgent.addActionListener(new ActionListener() {

			public void actionPerformed(ActionEvent arg0) {
				
				if(showFake){
					newViewPnl.showFakeAgent(false);
					showFake = false;
					showFakeAgent.setText("Show Proxy Agent");

				}else{
					newViewPnl.showFakeAgent(true);
					showFake = true;
					showFakeAgent.setText("Hide Proxy Agent");
				}
			
			}
			
		});
		
		zoomIn.addActionListener(new ActionListener(){

			@Override
			public void actionPerformed(ActionEvent arg0) {
				newViewPnl.zoomWithButtonClick(1);
			}
			
		});
		
		zoomOut.addActionListener(new ActionListener(){

			@Override
			public void actionPerformed(ActionEvent arg0) {
				newViewPnl.zoomWithButtonClick(-1);
			}

		});

		debug.addActionListener(new ActionListener(){

			@Override
			public void actionPerformed(ActionEvent arg0) {
		
				if(showDebugMode){
					newViewPnl.showDebugMode(false);
					showDebugMode = false;
					debug.setText("    Display Mode    ");
					debug.setIcon(displayIcon);
					
				}else{
					newViewPnl.showDebugMode(true);
					showDebugMode = true;
					debug.setText("     Debug Mode    ");
					debug.setIcon(debugIcon);
				}
			}

		});
		
		annotationLevel.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				currAnnotLevel = (currAnnotLevel+1)%4;
				boolean showAimsun = (currAnnotLevel==1 || currAnnotLevel==3);
				boolean showMitsim = (currAnnotLevel==2 || currAnnotLevel==3);
				newViewPnl.setAnnotationLevel(showAimsun, showMitsim);
				annotationLevel.setText((showAimsun&&showMitsim)?"Both annotations":showAimsun?"Aimsun annotations":showMitsim?"Mitsim annotations":"No annotations");
				annotationLevel.setIcon((showAimsun&&showMitsim)?alvl_Both:showAimsun?alvl_Aimsun:showMitsim?alvl_Mitsim:alvl_None);
			}
		});
		
		graphToShow.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				currGraphShown = (currGraphShown+1)%3;
				newViewPnl.setGraphVisible(currGraphShown==1, currGraphShown==2);
				graphToShow.setText(currGraphShown==2?"Walking graph":currGraphShown==1?"Driving graph":"Hide graphs");
				graphToShow.setIcon(currGraphShown==2?graphVis_Ped:currGraphShown==1?graphVis_Driver:graphVis_None);
			}
		});
		
		renderVideo.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				//Nothing to render?
				if (simData==null) {
					return;
				}
				
				//Stop animation
				if (animTimer.isRunning()) {
					animTimer.stop();
					playBtn.setIcon(playIcon);
				}
				
				//Request params
				VideoEncodeDialog vd = new VideoEncodeDialog(MainFrame.this, newViewPnl.getCurrFrameTick(), newViewPnl.getMaxFrameTick());
				vd.setLocationRelativeTo(MainFrame.this);
				vd.setVisible(true);
				
				//Nothing?
				if (vd.getOutFileName().isEmpty()) {
					return;
				}
				
				//Render
				new RenderToFileThread(vd.getOutFileName(), vd.getOutFileQuality(), vd.getOutFileFirstFrame(), vd.getOutFileLastFrame(), vd.getShowFrameNumber()).start();
			}
		});
		
		
		//This button causes the current view to become square.
		squareViewport.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				newViewPnl.zoomFitSquare();
			}
		});

		
		openEmbeddedFile.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				new FileOpenThread(true).start();
			}
		});
		
		
		openLogFile.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				new FileOpenThread(false).start();
			}
		});
		

	}
	
	private void resetTrackAgentIDs(HashSet<Long> allIds) {
		trackAgentIDs.removeAllItems();
		trackAgentIDs.addItem(new StringItem("Track no Agent", -1));
		if (allIds!=null) {
			//Sort
			Long[] ids_sorted = allIds.toArray(new Long[]{});
			Arrays.sort(ids_sorted);
			
			//Add
			for (Long it : ids_sorted) {
				trackAgentIDs.addItem(new StringItem("Track Agent " + it.intValue(), it.intValue()));
			}
		}
	}
	
	
	//Helper
	class FileOpenThread extends Thread {
		boolean isEmbedded;
		FileOpenThread(boolean isEmbedded) {
			this.isEmbedded = isEmbedded;
		}
		
		public void run() {
			//Pause the animation
			if (animTimer.isRunning()) {
				animTimer.stop();
				playBtn.setIcon(playIcon);
			}
			
			//Use a FileChooser
			File f = null;
			if (!isEmbedded) {
				final JFileChooser fc = new JFileChooser("src/res/data");
				if (fc.showOpenDialog(MainFrame.this)!=JFileChooser.APPROVE_OPTION) {
					return;
				}
				f = fc.getSelectedFile();
			}
	
			//Load the default visualization
			RoadNetwork rn = null;
			String fileName;
			try {
				BufferedReader br = null;
				if (isEmbedded) {
					br = Utility.LoadFileResource("res/data/default.log.txt");
					fileName = "default.log";
				} else {
					br = new BufferedReader(new FileReader(f));
					fileName = f.getName();
				}

				rn = new RoadNetwork();
//				System.out.println("before rn.loadFileAndReport");
				rn.loadFileAndReport(br, 0, null);
				br.close();
			} catch (IOException ex) {
				throw new RuntimeException(ex);
			}			
			
			console.setText("Input File Name: "+fileName);
			
			//Clear our global scaled points array.
			ScaledPoint.updateScaleAndTranslate(null, null);
			//Store all Agents returned by this.
			HashSet<Long> uniqueAgentIDs = new HashSet<Long>();
			//Load the simulation's results
			try {
				BufferedReader br = null;
				long fileSize = 0;
				if (isEmbedded) {
					br = Utility.LoadFileResource("res/data/default.log.txt");
				} else {
					br = new BufferedReader(new FileReader(f));
					fileSize = f.length();
				}
				simData = new SimulationResults();
				simData.loadFileAndReport(br, rn, uniqueAgentIDs, fileSize, newViewPnl);
				br.close();
			} catch (IOException ex) {
				throw new RuntimeException(ex);
			}
			
			//Reset our Agent ID combo box.
			resetTrackAgentIDs(uniqueAgentIDs);
			
			//Update the slider
			frameTickSlider.setMinimum(0);
			frameTickSlider.setMaximum(simData.ticks.size()-1);
			frameTickSlider.setMajorTickSpacing(simData.ticks.size()/10);
			frameTickSlider.setMinorTickSpacing(simData.ticks.size()/50);
			frameTickSlider.setValue(0);
			
			//Add a visualizer
			NetworkVisualizer vis = new NetworkVisualizer(MainFrame.this);
			vis.setSource(rn, simData, new Point(newViewPnl.getWidth(), newViewPnl.getHeight()), fileName);
			
			//Update the map
			newViewPnl.initMapCache(vis);
			
		}//run()
	}//class Thread
	
	
	public void updatePercentDrawn(double percent) {
		//Set the percent filled
		drawnPercent.setValue((int)(percent*100));
		
		//Color it depending on the health, 10% to 90%
		percent = (Math.max(Math.min(percent, 0.9), 0.1)-0.1)/0.8;
		double hue = ((1.0-percent) * 115)/360;
		drawnPercent.setForeground(new Color(Color.HSBtoRGB((float)hue, 1.0F, 0.9F)));
	}
	
	
	class RenderToFileThread extends Thread {
		String fileName;
		int quality;
		int firstFrame;
		int lastFrame;
		boolean showFrameNumber;
		
		private RenderToFileThread(String fileName, int quality, int firstFrame, int lastFrame, boolean showFrameNumber) {
			this.fileName = fileName;
			this.quality = quality;
			this.firstFrame = firstFrame;
			this.lastFrame = lastFrame;
			this.showFrameNumber = showFrameNumber;
		}
		
		public void run() {
			try {			
				IMediaWriter writer = ToolFactory.makeWriter(fileName);
				IRational frameRate = IRational.make(30,1); 
				if (writer.addVideoStream(0, 0, frameRate, newViewPnl.getWidth(), newViewPnl.getHeight())<0) {
					throw new RuntimeException("Couldn't add video stream.");
				}
		
				//Make sure we're encoding at quality 0 (highest)
				writer.getContainer().getStream(0).getStreamCoder().setGlobalQuality(quality);
				
				//Provide feedback to the user
				SwingUtilities.invokeLater(new ProgressUpdateRunner(newViewPnl, 0.0, false, new Color(0x00, 0x66, 0x00), ""));
				
				//Write through each frame
				int lastPercent = 0;
				int currPercent = 0;
				for (int i=firstFrame; i<=lastFrame; i++) {
					//Update
					double currPercentF = ((double)(i-firstFrame))/(lastFrame-firstFrame);
					currPercent = (int)(currPercentF*100);
					if (currPercent>lastPercent) {
						lastPercent = currPercent;
						SwingUtilities.invokeLater(new ProgressUpdateRunner(newViewPnl, currPercentF, true, new Color(0x00, 0x66, 0x00), "Encoding"));
					}
					
					//Get the buffered image for this frame.
					BufferedImage originalImage = newViewPnl.drawFrameToExternalBuffer(i, showFrameNumber, BufferedImage.TYPE_3BYTE_BGR);
					//BufferedImage worksWithXugglerBufferedImage = convertToType(originalImage, BufferedImage.TYPE_3BYTE_BGR);
					writer.encodeVideo(0, originalImage, (i-firstFrame)*simData.frame_length_ms, TimeUnit.MILLISECONDS);
				}
				
				//Finalize and close the image.
				writer.close();
		
				//And update our display
				System.out.println("Done");
				SwingUtilities.invokeLater(new Runnable() {
					public void run() {
						newViewPnl.jumpAnim(frameTickSlider.getValue(), frameTickSlider);
					}
				});
			} catch (Throwable t) {
				System.out.println("Exception while rendering to file: " + t.getClass().getName());
				System.out.println(t.getMessage());
				t.printStackTrace();
			}
		}
	}
	
	
	//////////////////////////////////////////////////
	// Code for mangling our various path variables. 
	//////////////////////////////////////////////////
	
	
	private void loadXuggler() {
		//String path = System.getenv().containsKey("LD_LIBRARY_PATH") ? System.getenv("LD_LIBRARY_PATH")+":" : "";
		
		//Try loading the library.
		System.loadLibrary("xuggle-xuggler");
		
		//If we didn't throw an exception, we're good.
		renderVideo.setEnabled(true);
	}
	
	private void hotlinkXuggler() throws NoSuchFieldException, IllegalAccessException {
		File xugglerDir = new File("libs-native");
		String xugglerPath = xugglerDir.getAbsolutePath();
		
		System.out.println("Attempting to patch in Xuggler: " + xugglerPath);
		if (xugglerDir.exists() && xugglerDir.isDirectory()) {
			mangleSystemPath(xugglerPath);
		}
	}
	
	
	private void mangleSystemPath(String xugglerPath) throws NoSuchFieldException, IllegalAccessException {
		//Set java.library.path, or JNI can't find the library.
		String path = System.getProperties().containsKey("java.library.path") ? System.getProperty("java.library.path")+":" : "";
		System.setProperty( "java.library.path", path+xugglerPath);
		
		//Kind of a hack: refresh a system property at runtime.
		Field fieldSysPath = ClassLoader.class.getDeclaredField("sys_paths");
		fieldSysPath.setAccessible( true );
		fieldSysPath.set(null, null);
	}
		
}


