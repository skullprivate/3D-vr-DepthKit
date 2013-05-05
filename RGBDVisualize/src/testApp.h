#pragma once

#include "ofMain.h"

#include "ofxRGBDCPURenderer.h"
#include "ofxRGBDGPURenderer.h"
#include "ofxRGBDVideoDepthSequence.h"
#include "ofxGameCamera.h"
#include "ofxTimeline.h"
#include "ofxTLVideoTrack.h"
#include "ofxTLVideoDepthAlignmentScrubber.h"
#include "ofxTLDepthImageSequence.h"
#include "ofxMSAInteractiveObjectDelegate.h"
#include "ofxTLCameraTrack.h"
#include "ofxDepthHoleFiller.h"
#include "ofxRGBDScene.h"
#include "ofxRGBDPlayer.h"
#include "ofxGui.h"
#include "ofxObjLoader.h"
#include "ofxRGBDCombinedVideoExporter.h"

typedef struct {
	ofxRGBDScene scene;
    ofxMSAInteractiveObjectWithDelegate* button;
} SceneButton;

typedef struct {
    string compositionFolder;
    ofxMSAInteractiveObjectWithDelegate* toggle;
    ofxMSAInteractiveObjectWithDelegate* load;
    bool inRenderQueue;
} CompButton;

typedef struct {
    SceneButton* sceneButton;
    bool completed;
    string compositionFolder;
    string compShortName;
    ofxMSAInteractiveObjectWithDelegate* remove;
} RenderButton;

class testApp : public ofBaseApp, public ofxMSAInteractiveObjectDelegate {

  public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
 	
	void updateRenderer();
	void drawGeometry();
	
	bool createNewComposition();
	bool loadDepthSequence(string path);
	bool loadVideoFile(string hiResPath, string lowResPath); //hires can be ""
	bool loadAlignmentMatrices(string path);
	
    void loadShaders();
    
	ofxXmlSettings projectsettings;
	void loadNewMediaBin();
	void populateScenes();
    void positionSceneButtons();
    
    void populateCompositionsForScene();
    void populateRenderQueue();

	void clearCompositionButtons();
	void clearRenderQueue();
	
	void newComposition();
    void loadDefaults();
	void saveComposition();
	bool loadComposition(string compositionDirectory);
	void setCompositionButtonName();
	
	bool loadAssetsForScene(SceneButton* scene);
    void resetCameraPosition();
    void checkReallocateFrameBuffers();
    void allocateFrameBuffers();
    
    ofxPanel gui;
    ofxFloatSlider videoVolume;
    ofxToggle drawPointcloud;
    ofxToggle drawWireframe;
    ofxToggle drawMesh;
    ofxToggle selfOcclude;
    ofxToggle drawDOF;
	
    ofxToggle shouldResetCamera;
    ofxFloatSlider cameraSpeed;
    ofxFloatSlider cameraRollSpeed;
    ofxToggle shouldSaveCameraPoint;
    ofxToggle currentLockCamera; 
	ofxToggle drawScanlinesVertical;
	ofxToggle drawScanlinesHorizontal;
	
	ofxToggle renderStillFrame;
	
	ofxToggle sinDistort;
	ofVec2f sinPosition;
	
	bool currentDrawScanlinesVertical;
	bool currentDrawScanlinesHorizontal;
	float currentScanlineStepVertical;
	float currentScanlineStepHorizontal;
	
	ofMesh verticalScanlineMesh;
	ofMesh horizontalScanlineMesh;
	
	void generateScanlineMesh(bool verticalScanline, bool horizontalScanline);
	
    ofxToggle currentMirror;
	ofxToggle flipTexture; //Debug for some grphx cards
    ofxToggle lockTo720p;
    ofxToggle lockTo1080p;
    ofxIntSlider customWidth;
    ofxIntSlider customHeight;
    ofxToggle setCurrentSize;

	
	
	ofxToggle drawShape;
	ofxIntSlider shapeVerts;
	ofMesh shapeMesh;
	void generateShapeMesh();
	
    ofxToggle fillHoles;
    ofxIntSlider currentHoleKernelSize;
    ofxIntSlider currentHoleFillIterations;
    ofxToggle temporalAlignmentMode;
    ofxToggle captureFramePair;

    ofxToggle renderObjectFiles;
	ofxToggle includeTextureMaps;
	ofxToggle renderRainbowVideo;
    ofxToggle startSequenceAt0;

	bool multisampleBufferAllocated;
    bool currentRenderObjectFiles;
    bool firstRenderFrame;
    bool startRenderMode;
	//MSA Object delegate
    ofxMSAInteractiveObjectWithDelegate* mediaBinButton;
    ofxMSAInteractiveObjectWithDelegate* changeCompButton;
	ofxMSAInteractiveObjectWithDelegate* newCompButton;
	ofxMSAInteractiveObjectWithDelegate* saveCompButton;
    ofxMSAInteractiveObjectWithDelegate* saveCompAsNewButton;
    ofxMSAInteractiveObjectWithDelegate* renderBatch;
    
    void setButtonColors(ofxMSAInteractiveObjectWithDelegate* btn);
    
    vector<SceneButton> scenes;
    vector<CompButton> comps;
    vector<RenderButton> renderQueue;
    float maxSceneX;
	
	SceneButton* selectedScene;
    CompButton* selectedComp;
    SceneButton* loadedScene;
    
 	void objectDidRollOver(ofxMSAInteractiveObject* object, int x, int y);
    void objectDidRollOut(ofxMSAInteractiveObject* object, int x, int y);
	void objectDidPress(ofxMSAInteractiveObject* object, int x, int y, int button);	
	void objectDidRelease(ofxMSAInteractiveObject* object, int x, int y, int button);	
	void objectDidMouseMove(ofxMSAInteractiveObject* object, int x, int y);
    
    bool isSceneLoaded;
    
	void populateTimelineElements();
	int renderQueueIndexToRemove;
	
	void addCompToRenderQueue(CompButton* comp);
	void finishRender();
    
    string currentCompShortName;
	string currentCompositionDirectory;
	string currentCompositionFile;
    string currentCompositionLabel;
	string currentVideoFrameFile;
	string mediaBinFolder;
	
    bool viewComps;
    float accumulatedPerlinOffset;
    
	ofxGameCamera cam;
	ofxTLCameraTrack* cameraTrack;
	
	ofxTimeline timeline;
	ofxTLVideoTrack* videoTrack;
	
	ofxRGBDPlayer player;
	ofxRGBDGPURenderer renderer;
    ofxRGBDCPURenderer meshBuilder;
    ofxRGBDCombinedVideoExporter rainbowExporter;
	ofTexture combinedVideoTexture;
	
	ofxTLDepthImageSequence depthSequence;
	ofxTLVideoDepthAlignmentScrubber alignmentScrubber;
	ofxDepthHoleFiller holeFiller;

	ofRectangle fboRectangle;    
    ofRectangle depthAlignAssistRect;
    ofRectangle colorAlignAssistRect;

    ofShader dofRange;
    ofShader dofBlur;
    ofVboMesh dofQuad;
    
	ofFbo fbo1;
    ofFbo swapFbo; //used for temp drawing
    ofFbo dofBuffer; //used to get a solid depth texture

	ofImage savingImage;
	string saveFolder;
	string lastSavedDate;    
	
	int rainbowVideoFrame;
	bool timelineElementsAdded;
	bool currentlyRendering;
	int currentRenderFrame;
    
	//used for temporal aligmnet nudging
	int currentDepthFrame;
	int currentVideoFrame;
	bool rendererDirty;
    ofNode renderedCameraPos;
    
	string pathDelim;	
};
