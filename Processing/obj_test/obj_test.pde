import peasy.*;
import controlP5.*; // controlP5ライブラリを読み込む

ControlP5 cp5; // controlP5をcp5として宣言する
Slider boxSize; // スライダー:立方体のサイズ
ColorWheel col; // カラー:立方体の色
Toggle start; // トグルボタン:スタート/ストップ
ColorWheel col2;
Slider distance;
Slider distance2;

PeasyCam cam;




PShape s;
PShape s1;
PShape s2;
PShape s3;

void setup() {
  size(1500, 1500, P3D);
  cam = new PeasyCam(this, 100);
  
  cp5 = new ControlP5(this); 
  
  boxSize = cp5.addSlider("BOX SIZE") 
    .setPosition(20, 20)
    .setRange(0, 2)
    .setValue(1);
    
 distance = cp5.addSlider("d") 
    .setPosition(20, 40)
    .setRange(0, 50)
    .setValue(0); 
    
    distance2 = cp5.addSlider("d2") 
    .setPosition(20, 60)
    .setRange(-500, 500)
    .setValue(0); 
    
 col = cp5.addColorWheel("COLOR")
    .setPosition(20, 80)
    .setRGB(color(31, 128, 255));
    
 col2 = cp5.addColorWheel("COLOR2")
    .setPosition(20, 300)
    .setRGB(color(31, 128, 255));   
    
  cp5.setAutoDraw(false);
  
  s = loadShape("test.obj");
  s1 = loadShape("b1.obj");
  s2 = loadShape("b2.obj");
  s3 = loadShape("b3.obj");
  
}

void draw() {

  background(200);
  pushMatrix();
  
  directionalLight(126, 126, 126, 0, -5, 0);
  //directionalLight(126, 126, 126, 0, 0, -5);
  directionalLight(126, 126, 126, -5, 0, 0);
  directionalLight(126, 126, 126, 0, 5, 0);
  //directionalLight(126, 126, 126, 0, 0, 5);
  directionalLight(126, 126, 126, 5, 0, 0);
  ambientLight(122, 122, 122);
  
    for(int i = 0; i < 8; i ++){   
    translate(-distance.getValue(),0,0);
    rotateY(PI/4);
    shape(s, -distance.getValue()/PI,0);
    }
    
    
    
    for(int i = 0; i < 4; i ++){   
    translate(-distance.getValue(),0,0);
    rotateY(PI/4);
    shape(s1, -distance.getValue()/PI,0);
    
    translate(-distance.getValue(),0,0);
    //shape(s2, -distance.getValue()/PI,0);
    rotateY(PI/4);
    }
    

    for(int i = 0; i < 4; i ++){   
    translate(-distance.getValue(),0,0);
    rotateY(PI/4);
    shape(s2, -distance.getValue()/PI,0);
    
    translate(-distance.getValue(),0,0);
    //shape(s2, -distance.getValue()/PI,0);
    rotateY(PI/4);
    }

    
    

  rotateY(PI/4);  
  shape(s3, -distance.getValue(), 0);
  
  
  translate(width/2, height/2);
  s.setFill(col.getRGB());
  s1.setFill(col2.getRGB());
  s2.setFill(col2.getRGB());
  s3.setFill(col2.getRGB());
  
  s.setStroke(true);
  s.setStroke(color(0, 0, 0));
   //s.setStrokeWeight(1.2f);


  
  popMatrix();
  
  gui();
  
}


void gui() {  
  noLights();
  hint(DISABLE_DEPTH_TEST);
  cam.beginHUD();
  cp5.draw();
  cam.endHUD();
  hint(ENABLE_DEPTH_TEST);
}