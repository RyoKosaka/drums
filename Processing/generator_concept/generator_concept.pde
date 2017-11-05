import peasy.*;
import controlP5.*;

ControlP5 cp5;

int HOLENUMBER;
int LEGNUMBER; 
int COLOR;
int COLOR2;
int OPEN1;

PeasyCam cam;


PShape s;
PShape e;
PShape h;
PShape t;

PShape bs;
PShape be;
PShape bh;
PShape bt;
PShape bl;
PShape bb;


void setup() {
  size(1200, 800, P3D);
  cam = new PeasyCam(this, 100);
  cp5 = new ControlP5(this); 
  
  cp5.addSlider("HOLENUMBER") 
    .setPosition(20, 20)
    .setRange(0, 16)
    .setValue(8);
    
  cp5.addSlider("LEGNUMBER") 
    .setPosition(20, 40)
    .setRange(0, 10)
    .setValue(0); 
    
  //cp5.addSlider("SEPARATE") 
  //  .setPosition(20, 60)
  //  .setRange(0, 10)
  //  .setValue(0);
    
  cp5.addSlider("OPEN1") 
    .setPosition(20, 60)
    .setRange(0, 50)
    .setValue(0);  
    
    
  cp5.addColorWheel("COLOR")
    .setPosition(20, 100)
    .setRGB(color(31, 128, 255));   
    
  cp5.addColorWheel("COLOR2")
    .setPosition(20, 320)
    .setRGB(color(31, 128, 255));     
    
  cp5.setAutoDraw(false);
  
  s = loadShape("rim_start.obj");
  e = loadShape("rim_end.obj");
  h = loadShape("rim_hole.obj");
  t = loadShape("rim_tube.obj");
  
  bs = loadShape("bottom_start.obj");
  be = loadShape("bottom_end.obj");
  bh = loadShape("bottom_hole.obj");
  bt = loadShape("bottom_tube.obj");
  bl = loadShape("bottom_leg.obj");
  bb = loadShape("bottom_base.obj");
  
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
  

/////////////////////////////////////RIM////////////////////////////////////////  
  
  for(int i = 0; i < HOLENUMBER; i ++){   
    translate(OPEN1,0,0);
    
    shape(s, 0,0);
    //rotateY(-1*(PI/HOLENUMBER-PI/16));
    
    for(int j = 0; j < (48/HOLENUMBER)-3; j ++){
    shape(t, 0,0);
    rotateY(-1*(PI/48));
    }
    
    shape(h, 0,0);
    //rotateY(-1*(PI/HOLENUMBER-PI/16)-(PI/12));
    
    rotateY(-1*(PI/12));
    
    for(int k = 0; k < (48/HOLENUMBER)-3; k ++){
    shape(t, 0,0);
    rotateY(-1*(PI/48));
    }
    
    shape(e, 0,0);
    rotateY(-1*PI/24);
    }
    


     if(HOLENUMBER == 0){
     
      for(int j = 0; j < 96; j ++){
        //rotateY(PI/48);
        shape(t,0,0); 
        rotateY(-PI/48);
        }      
      
    }
  
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////BOTTOM//////////////////////////////////////////

  for(int i = 0; i < HOLENUMBER; i ++){   
    translate(OPEN1,0,0);
    
    shape(bs, 0,0);
    //rotateY(-1*(PI/HOLENUMBER-PI/16));
    
    for(int j = 0; j < (48/HOLENUMBER)-3; j ++){
    shape(bt, 0,0);
    rotateY(-1*(PI/48));
    }
    
    shape(bh, 0,0);

    //rotateY(-1*(PI/HOLENUMBER-PI/16)-(PI/12));
    
    rotateY(-1*(PI/12));
    
    for(int k = 0; k < (48/HOLENUMBER)-3; k ++){
    shape(bt, 0,0);
    rotateY(-1*(PI/48));
    }
    
    shape(be, 0,0);
    rotateY(-1*PI/24);
    }
    
    
    //shape(bb, 0,0);
    

     if(HOLENUMBER == 0){
     
      for(int j = 0; j < 96; j ++){
        //rotateY(PI/48);
        shape(bt,0,0); 
        rotateY(-PI/48);
        }      
      
    }


/////////////////////////////////////////////////////////////////////////////////

///////////////////////////////BOTTOM LEG////////////////////////////////////////




    for(int i = 0; i < LEGNUMBER; i ++){   
    //translate(-distance.getValue(),0,0);
    shape(bl, 0,0);
    rotateY(-2*PI/LEGNUMBER);
    }




/////////////////////////////////////////////////////////////////////////////////
    

  

    
  translate(width/2, height/2);
  t.setFill(COLOR);
  h.setFill(COLOR);
  s.setFill(COLOR);
  e.setFill(COLOR);
  
  bt.setFill(COLOR2);
  bh.setFill(COLOR2);
  bl.setFill(COLOR2);
  bb.setFill(COLOR2);
  be.setFill(COLOR2);
  bs.setFill(COLOR2);

  
  //t.setStroke(true);
  //t.setStroke(color(0, 0, 0));
  //t.setStrokeWeight(1.2f);
  
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