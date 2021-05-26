#target AfterEffects

/**************************************
Scene : Scene
Resolution : 1920 x 1080
Duration : 10.416667
FPS : 24.000000
Date : 2018-09-04 18:14:30.831913
Exported with io_export_after_effects.py
**************************************/



function compFromBlender(){

var compName = prompt("Blender Comp's Name \nEnter Name of newly created Composition","BlendComp","Composition's Name");
if (compName){
var newComp = app.project.items.addComp(compName, 1920, 1080, 1.000000, 10.416667, 24.000000);
newComp.displayStartTime = 0.083333;


// **************  CAMERA 3D MARKERS  **************


// **************  OBJECTS  **************


var _01_low = newComp.layers.addNull();
_01_low.threeDLayer = true;
_01_low.source.name = "_01_low";
_01_low.property("position").setValue([965.561876,530.366507,1004.807281],);
_01_low.property("orientation").setValue([-90.000000,-0.000000,0.000000],);
_01_low.property("scale").setValue([100.000000,100.000000,100.000000],);


var _09_low = newComp.layers.addNull();
_09_low.threeDLayer = true;
_09_low.source.name = "_09_low";
_09_low.property("position").setValue([960.000000,540.000000,213.150358],);
_09_low.property("orientation").setValue([-90.000000,-0.000000,0.000000],);
_09_low.property("scale").setValue([100.000000,100.000000,100.000000],);


var _11_low = newComp.layers.addNull();
_11_low.threeDLayer = true;
_11_low.source.name = "_11_low";
_11_low.property("position").setValue([960.000000,540.000000,213.119125],);
_11_low.property("orientation").setValue([-90.000000,-0.000000,0.000000],);
_11_low.property("scale").setValue([100.000000,100.000000,100.000000],);


var _16_low = newComp.layers.addNull();
_16_low.threeDLayer = true;
_16_low.source.name = "_16_low";
_16_low.property("position").setValue([971.123800,540.000000,1004.807281],);
_16_low.property("orientation").setValue([-90.000000,-0.000000,0.000000],);
_16_low.property("scale").setValue([100.000000,100.000000,100.000000],);


var _02_low = newComp.layers.addNull();
_02_low.threeDLayer = true;
_02_low.source.name = "_02_low";
_02_low.property("position").setValue([960.000000,540.000000,168.633890],);
_02_low.property("orientation").setValue([-90.000000,-0.000000,0.000000],);
_02_low.property("scale").setValue([100.000000,100.000000,100.000000],);


var _12_low = newComp.layers.addNull();
_12_low.threeDLayer = true;
_12_low.source.name = "_12_low";
_12_low.property("position").setValue([954.438100,530.366507,1004.807281],);
_12_low.property("orientation").setValue([-90.000000,-0.000000,0.000000],);
_12_low.property("scale").setValue([100.000000,100.000000,100.000000],);


var _05_low = newComp.layers.addNull();
_05_low.threeDLayer = true;
_05_low.source.name = "_05_low";
_05_low.property("position").setValue([960.000000,188.603892,-91.429472],);
_05_low.property("orientation").setValue([-90.000000,-0.000000,0.000000],);
_05_low.property("scale").setValue([100.000000,100.000000,100.000000],);


var _10_low = newComp.layers.addNull();
_10_low.threeDLayer = true;
_10_low.source.name = "_10_low";
_10_low.property("position").setValue([960.000000,540.000001,988.467598],);
_10_low.property("orientation").setValue([-90.000000,-0.000000,0.000000],);
_10_low.property("scale").setValue([100.000000,100.000000,100.000000],);


var _13_low = newComp.layers.addNull();
_13_low.threeDLayer = true;
_13_low.source.name = "_13_low";
_13_low.property("position").setValue([948.876200,540.000002,1004.807281],);
_13_low.property("orientation").setValue([-90.000000,-0.000000,0.000000],);
_13_low.property("scale").setValue([100.000000,100.000000,100.000000],);


var _03_low = newComp.layers.addNull();
_03_low.threeDLayer = true;
_03_low.source.name = "_03_low";
_03_low.property("position").setValue([960.000000,540.027720,168.633890],);
_03_low.property("orientation").setValue([-90.000000,-0.000000,0.000000],);
_03_low.property("scale").setValue([100.000000,100.000000,100.000000],);


var _15_low = newComp.layers.addNull();
_15_low.threeDLayer = true;
_15_low.source.name = "_15_low";
_15_low.property("position").setValue([965.561924,549.633494,1004.807281],);
_15_low.property("orientation").setValue([-90.000000,-0.000000,0.000000],);
_15_low.property("scale").setValue([100.000000,100.000000,100.000000],);


var _04_low = newComp.layers.addNull();
_04_low.threeDLayer = true;
_04_low.source.name = "_04_low";
_04_low.property("position").setValue([960.000000,188.603892,-150.080872],);
_04_low.property("orientation").setValue([-90.000000,-0.000000,0.000000],);
_04_low.property("scale").setValue([100.000000,100.000000,100.000000],);


var _08_low = newComp.layers.addNull();
_08_low.threeDLayer = true;
_08_low.source.name = "_08_low";
_08_low.property("position").setValue([960.000000,311.674156,-12.434387],);
_08_low.property("orientation").setValue([-90.000000,-0.000000,0.000000],);
_08_low.property("scale").setValue([100.000000,100.000000,100.000000],);


var _14_low = newComp.layers.addNull();
_14_low.threeDLayer = true;
_14_low.source.name = "_14_low";
_14_low.property("position").setValue([954.438100,549.633496,1004.807281],);
_14_low.property("orientation").setValue([-90.000000,-0.000000,0.000000],);
_14_low.property("scale").setValue([100.000000,100.000000,100.000000],);


var _07_low = newComp.layers.addNull();
_07_low.threeDLayer = true;
_07_low.source.name = "_07_low";
_07_low.property("position").setValue([960.000000,311.674156,-12.434387],);
_07_low.property("orientation").setValue([-90.000000,-0.000000,0.000000],);
_07_low.property("scale").setValue([100.000000,100.000000,100.000000],);


var _06_low = newComp.layers.addNull();
_06_low.threeDLayer = true;
_06_low.source.name = "_06_low";
_06_low.property("position").setValue([960.000000,310.603347,-14.780807],);
_06_low.property("orientation").setValue([-90.000000,-0.000000,0.000000],);
_06_low.property("scale").setValue([100.000000,100.000000,100.000000],);


// **************  LIGHTS  **************


// **************  CAMERAS  **************



}else{alert ("Exit Import Blender animation data \nNo Comp's name has been chosen","EXIT")};}


app.beginUndoGroup("Import Blender animation data");
compFromBlender();
app.endUndoGroup();


