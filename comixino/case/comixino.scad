/*
 Decription: Comixino case
 Author: issalig
 Date: 10/05/25
 */
width = 81.13;//87.6; //24
height = 68.1; //40
thick_hor = 2.4;
deep = 20;
int_support_height=3;

depth=20;
thick_vert = thick_hor /2;
thick_dent = 1;
depth_dent = 3.2;//thick_hor /2;
fillet_r = thick_hor;
groove_d = 0.5;
groove_length = 6;
groove_deep = 1.4;
groove_height = 0.25+0.01;  //0.01 solo en tab ojo

joint_dent_offset = 0.8; //space between two halfs when mounted


hole_m3 = 3;
hole0_offx = 38.11;
hole0_offy = 20.54;

//under screen
hole1_offx = 36.57;//38.11;
hole1_offy = 37.65;//37.64;//32.65;

//up right
hole2_offx = 70.90;
hole2_offy = 63.95;//58.95;
//down right
hole3_offx = 70.90;
hole3_offy = 4.05;

//up left
hole4_offx = 14.50;
hole4_offy = 63.95;

//down left
hole5_offx = 4.35;
hole5_offy = 4.05;

//buttons
button_offx = 13;
button_offy = 5.6;
button_deltax = 8.058;
button_radius =2.25;

screen_offx = 23.8;
screen_offy = 24.9;

screen_width = 27;
screen_height = 22;

screen2_offx =19.3;
screen2_offy = 39.74;

screen2_width = 37.95;
screen2_height =12;

edge_height = 58.02+1;
edge_offx = 0;
edge_offy =4.99;

arduino_offx=4.9;
arduino_offy=23.18;

sd_offx=51.45;
sd_offy=25.75;


//leds
led1_offx = 53.67;
led1_offy = 21.95;
led2_offx = 60.02;
led2_offy = 21.95;
led_diam = 3;

pcb_deep=1.5+0.1;

module pcb(){
    union(){
        translate([-11.371,4.99,0])
            cube([11.423,58.07,pcb_deep]);
        #cube([87.58,68.43,pcb_deep]);
        }
}

module pcb_bbox(h=13.6){
    union(){
        translate([-11.371,4.99,0])
            cube([11.423,58.07,h]);
        #cube([87.58,68.43,h]);
        }
}



module sd(deep=pcb_deep){
    cube([23,42,deep]);
}

module arduino(deep=pcb_deep){
    cube([18.28, 46.22, deep]);
    translate([5.19, 35.68,0])
        cube([7.88, 10.42, deep*5]);
}

module cube_raiser(){
    cube([14,86,11.9]);
}

//translate([0,0,int_support_height])
//color("black")
//#pcb_bbox();

module button_cap(deep=10, r=2.5){
    translate([0,0,2])
    cylinder(h=deep-2, r=r, $fn=60);
    difference(){
        cylinder(h=2,d=3.5+3, $fn=60);
        cylinder(h=0.5,d=3.5, $fn=60);
    }
}

module int_support(){
    translate([0,0,-thick_hor*0])
        cylinder(h=int_support_height, r=thick_hor, $fn=60);
    translate([0,height,-thick_hor*0])
        cylinder(h=int_support_height, r=thick_hor, $fn=60);
    translate([width,0,-thick_hor*0])
        cylinder(h=int_support_height, r=thick_hor, $fn=60);
    translate([width,height,-thick_hor*0])
        cylinder(h=int_support_height, r=thick_hor, $fn=60);    
}

module screws_hole(hole_depth=100){
    /*hole1_offx = 38.11;
    hole1_offy = 32.65;
    hole2_offx = 77.35;
    hole2_offy = 58.95;
    hole3_offx = 77.35;
    hole3_offy = 4.04;
    */

    /*
    #translate([hole1_offx, hole1_offy,0]){
        cylinder(h=hole_depth, d=3-0.2, $fn=60);
        cylinder(h=thick_vert, d1=5.6, d2=3-0.2, $fn=60);
    }
        
    #translate([hole2_offx, hole2_offy,0]){
        cylinder(h=hole_depth, d=3, $fn=60);
        cylinder(h=thick_vert, d1=5.6, d2=3, $fn=60);
        }
        
    */    
    #translate([hole3_offx, hole3_offy,0]){
        cylinder(h=hole_depth, d=3, $fn=60);
        cylinder(h=thick_vert, d1=5.6, d2=3, $fn=60);            
    }
    
    
}

module screws_down(depth=20, hole_depth=50, hole=false){
    /*
    hole1_offx = 38.11;
    hole1_offy = 32.65;
    hole2_offx = 77.35;
    hole2_offy = 58.95;
    hole3_offx = 77.35;
    hole3_offy = 4.04;
    */
   
    cl = 0.2;
    
    difference(){
        union(){
            translate([hole1_offx, hole1_offy,0])
            cylinder(h=depth, d=hole_m3*3, $fn=60);
            translate([hole2_offx, hole2_offy,0])
            cylinder(h=depth, d=hole_m3*3, $fn=60);
            translate([hole3_offx, hole3_offy,0])
            cylinder(h=depth, d=hole_m3*3, $fn=60);
            translate([hole4_offx, hole4_offy,0])
            cylinder(h=depth, d=hole_m3*3, $fn=60);
            translate([hole5_offx, hole5_offy,0])
            cylinder(h=depth, d=hole_m3*3, $fn=60);            
        }
            translate([hole1_offx, hole1_offy,0])
            cylinder(h=hole_depth, d=hole_m3-cl, $fn=60);
        
    if (hole){        
            translate([hole2_offx, hole2_offy,0])
            cylinder(h=hole_depth, d=hole_m3-cl, $fn=60);
        }
            translate([hole3_offx, hole3_offy,0])
            cylinder(h=hole_depth, d=hole_m3-cl, $fn=60);
                
    }
    
    //centering cylinder
    if (!hole){
            //translate([hole1_offx, hole1_offy,0])
            //cylinder(h=int_support_height+pcb_deep, d=3-cl, $fn=60);
            translate([hole2_offx, hole2_offy,0])
            cylinder(h=int_support_height+pcb_deep, d=hole_m3-cl, $fn=60);
            //translate([hole3_offx, hole3_offy,0])
            //cylinder(h=int_support_height+pcb_deep, d=hole_m3-cl, $fn=60);
            translate([hole4_offx, hole4_offy,0])
            cylinder(h=int_support_height+pcb_deep, d=hole_m3-cl, $fn=60);
            translate([hole5_offx, hole5_offy,0])
            cylinder(h=int_support_height+pcb_deep, d=hole_m3-cl, $fn=60);
            
    }
}

module screws_up(depth=20, hole_depth=10, hole=false){

    //hole0_offx = 38.11;
    //hole0_offy = 20.54;
    //hole1_offx = 38.11;
    //hole1_offy = 32.65;
    /*
    hole2_offx = 77.35;
    hole2_offy = 58.95;
    hole3_offx = 77.35;
    hole3_offy = 4.04;
   */
   
    cl = 0.2;
    
    difference(){
        union(){
            //translate([hole0_offx, hole0_offy,0])
            //cylinder(h=depth, d=3+2, $fn=60);
            //translate([hole2_offx, hole2_offy,0])
            //cylinder(h=depth, d1=hole_m3+2, d2=3+4, $fn=60);
            translate([hole3_offx, hole3_offy,0])
            cylinder(h=depth, d1=hole_m3+2, d2=3+4, $fn=60);
        }
        if (hole){
            //translate([hole0_offx, hole0_offy,0])
            //cylinder(h=hole_depth, d=3, $fn=60);
            //translate([hole2_offx, hole2_offy,0])
            //cylinder(h=hole_depth, d=hole_m3-cl, $fn=60);
            translate([hole3_offx, hole3_offy,0])
            cylinder(h=hole_depth, d=hole_m3-cl, $fn=60);
        }        
    }
}

module conn_up_hole(){

translate([81.2,5.8,0])
cube([6.15, 56.95,30]);

}

module conn_side_hole(depth=5){
    //usb height 11.5 16.1
    translate([9.8, 68,int_support_height+pcb_deep+11.5])
    #cube([13.5-5,thick_hor*2,16.2-11.5]);
    
    //jumpers
    translate([19.53+4.5,68,depth])
    #cube([40.5,thick_hor*2,7]);
    
    //sd 
    translate([sd_offx+3, 68,int_support_height+pcb_deep+11.5])
    #cube([16, thick_hor*2, 16.2-11.5]);
    
    //translate([60.91+18/2, 68+46,int_support_height+pcb_deep+11.5])
    //cylinder(h=16.2-11.5+2+10, d=90, $fn=90);
}

module edge_hole(deep=10){
    cl = 0.1;
    translate([edge_offx-thick_hor, edge_offy-1/2,int_support_height-cl])
    cube([thick_hor*2, edge_height, deep]);
}

module led_hole(deep=100){
    cl=0.1;
    translate([led1_offx, led1_offy,0]){
        cylinder(h=deep, d=led_diam+cl, $fn=60);
    }
    translate([led2_offx, led2_offy,0]){
        cylinder(h=deep, d=led_diam+cl, $fn=60);
    }
}

module button_hole(deep=100){
    for(i=[0:1:6]){
    cl=0.1;
        translate([button_offx+i*button_deltax,button_offy,0]){
            cylinder(h=deep, r=button_radius+cl, $fn=60);
        }
    }
}

module button_hole_tube(deep=6){
    for(i=[0:1:6]){
        cl=0.1;
        translate([button_offx+i*button_deltax,button_offy,0]){
            difference(){
                cylinder(h=deep, r1=button_radius+1, r2=button_radius+1.5, $fn=60);
                cylinder(h=deep, r=button_radius+cl, $fn=60);
                }
        }
    }
}


module screen(deep=100){
    translate([screen_offx, screen_offy,0])
    cube([screen_width,screen_height,deep]);
}

//module half_case(depth=5, thick=1.8, thick2=0.8, inner=true){
module half_case(depth=5, thick=1.8, thick2=0.8, inner=true, base = false){
    //translate([-thick,-thick,-thick])
    //#cube([width+2*thick,height+2*thick,depth+thick]);
    
    difference(){
    
    union(){
        hull(){
            translate([0,0,0])
                cylinder(h=depth, r=thick_hor, $fn=60);
            translate([0,height,0])
                cylinder(h=depth, r=thick_hor, $fn=60);
            translate([width,0,0])
                cylinder(h=depth, r=thick_hor, $fn=60);
            translate([width,height,0])
                cylinder(h=depth, r=thick_hor, $fn=60);        
        }
    
    //inner    
    if (inner){
        //#translate([-thick2,-thick2,0])
        //cube([width+2*thick2,height+2*thick2,depth+2*thick2]);
        hull(){
            //inner rounded border
            translate([0,0,0])
            cylinder(h=depth+depth_dent+joint_dent_offset, r=thick_dent, $fn=60);
            translate([0,height,0])
            cylinder(h=depth+depth_dent+joint_dent_offset, r=thick_dent, $fn=60);
            translate([width,0,0])
            cylinder(h=depth+depth_dent+joint_dent_offset, r=thick_dent, $fn=60);
            translate([width,height,0])
            cylinder(h=depth+depth_dent+joint_dent_offset, r=thick_dent, $fn=60);        
        }     
                
        
                
        //tab cube
        translate([width*0.15-groove_length/2,-thick_dent-groove_height,depth+depth_dent+joint_dent_offset-groove_deep])
        {        
        cube([groove_length, groove_height, groove_deep]);
        }

        translate([width*0.85-groove_length/2,-thick_dent-groove_height,depth+depth_dent+joint_dent_offset-groove_deep])
        {        
        cube([groove_length, groove_height, groove_deep]);
        }        
 
         
        translate([width*0.15-groove_length/2,height+thick_dent,depth+depth_dent+joint_dent_offset-groove_deep])
        {        
        cube([groove_length, groove_height, groove_deep]);
        }

        translate([width*0.85-groove_length/2,height+thick_dent,depth+depth_dent+joint_dent_offset-groove_deep])
        {        
        cube([groove_length, groove_height, groove_deep]);
        }   

///// tabs in Y     
        translate([-thick_dent-groove_height,height*0.15-groove_length/2,depth+depth_dent+joint_dent_offset-groove_deep])
        {        
        cube([groove_height, groove_length, groove_deep]);
        }

        translate([-thick_dent-groove_height,height*0.85-groove_length/2,depth+depth_dent+joint_dent_offset-groove_deep])
        {        
        cube([groove_height, groove_length, groove_deep]);
        }  
       
        translate([width+thick_dent,height*0.15-groove_length/2,depth+depth_dent+joint_dent_offset-groove_deep])
        {        
        cube([groove_height, groove_length, groove_deep]);
        }

        translate([width+thick_dent,height*0.85-groove_length/2,depth+depth_dent+joint_dent_offset-groove_deep])
        {        
        cube([groove_height, groove_length, groove_deep]);
        }  
      
        
    } //end inner
    
    if (!inner) {
        border_cl = 0.15;
    
        difference(){
            hull(){
            translate([0,0,0])
                cylinder(h=depth+depth_dent, r=thick_hor, $fn=60);
                translate([0,height,0])
                cylinder(h=depth+depth_dent, r=thick_hor, $fn=60);
                translate([width,0,0])
                cylinder(h=depth+depth_dent, r=thick_hor, $fn=60);
                translate([width,height,0])
                cylinder(h=depth+depth_dent, r=thick_hor, $fn=60);        
            }
           
            hull(){
            translate([0,0,0])
                cylinder(h=depth+depth_dent, r=thick_dent+border_cl, $fn=60);
                translate([0,height,0])
                cylinder(h=depth+depth_dent, r=thick_dent+border_cl, $fn=60);
                translate([width,0,0])
                cylinder(h=depth+depth_dent, r=thick_dent+border_cl, $fn=60);
                translate([width,height,0])
                cylinder(h=depth+depth_dent, r=thick_dent+border_cl, $fn=60);
            } 
       
        cyl_cl = 0.2;
        groove_length2 = groove_length + 2*cyl_cl;
        groove_deep2 = groove_deep + cyl_cl; 
      
           //groove cube
        #translate([width*0.15-groove_length2/2-cyl_cl,-thick_dent-(groove_height+cyl_cl),depth])
        {        
        cube([groove_length2, groove_height+cyl_cl, groove_deep2]);
        }

        #translate([width*0.85-groove_length2/2-cyl_cl,-thick_dent-(groove_height+cyl_cl),depth])        {        
        cube([groove_length2, groove_height+cyl_cl, groove_deep2]);
        }        
 
         
        translate([width*0.15-groove_length2/2-cyl_cl,height+thick_dent,depth])
        {        
        cube([groove_length2, groove_height+cyl_cl, groove_deep2]);
        }

        #translate([width*0.85-groove_length2/2-cyl_cl,height+thick_dent,depth])
        {        
        cube([groove_length2, groove_height+cyl_cl, groove_deep2]);
        }   

//////////////////////////
        #translate([-thick_dent-(groove_height+cyl_cl),height*0.15-groove_length2/2-cyl_cl,depth])
        {        
        cube([groove_height+cyl_cl, groove_length2,  groove_deep2]);
        }

        #translate([-thick_dent-(groove_height+cyl_cl),height*0.85-groove_length2/2-cyl_cl,depth])
        {        
        cube([groove_height+cyl_cl, groove_length2,  groove_deep2]);
        }

        
        translate([width+thick_dent,height*0.15-groove_length2/2-cyl_cl,depth])
        {        
        cube([groove_height+cyl_cl, groove_length2,  groove_deep2]);
        }

        translate([width+thick_dent,height*0.85-groove_length2/2-cyl_cl,depth])
        {        
        cube([groove_height+cyl_cl, groove_length2,  groove_deep2]);
        }
        
        
        
        } 
    } //end outer
    
    }
    
    //remove inner volume
    cube([width,height,depth +depth_dent +joint_dent_offset+ 0.001]);
    
    //edge_hole();

    }
       
    //down fillet part
    if (base) {
        
        translate([0,0,-0*thick_vert])
        difference(){
        minkowski(){    
            hull(){        
                cylinder(h=0.00001, r=thick_vert, $fn=60);
            translate([0,height,0])
                cylinder(h=0.00001, r=thick_vert, $fn=60);
            translate([width,0,0])
                cylinder(h=0.00001, r=thick_vert, $fn=60);
            translate([width,height,0])
                cylinder(h=0.00001, r=thick_vert, $fn=60);        
            }
        sphere(r=thick_vert, $fn=60);
        }
        
        translate([-thick_hor,-thick_hor,0])    
        cube([width+2*thick_hor, height+2*thick_hor, thick_vert]);
        }
    }    
}

translate([-75.6-6.45,124.3+0,int_support_height+pcb_deep/2])
import("comixino.stl");

 
module symbols(deep=0.5){ 

    s=["\u25b2","\u25bc", "\u25b2", "\u25a0","@","\u25cf","R"];
    
    for(i=[0:1:len(s)]){    
        translate([i*button_deltax+button_offx,11,0]){                
            #linear_extrude(deep)
            if (i==2) {rotate([0,0,-90])
            text(s[i], size=4, valign="center", halign="center", font="Liberation Sans", $fn=30);
            }
            else
            text(s[i], size=4, valign="center", halign="center", font="Liberation Sans", $fn=30);
        }
    }
     echo(s);
}

$font_logo_name = "MicroExtendFLF:bold";
//https://www.whatfontis.com/FF_MicroExtendFLF-Bold.font

// logo
$logo_enabled = 1;          // show logo
$logo_text_enabled = true   ; // show font logo or text


// logo using font from keyboard
module logo(h=0.5, size=5.5)
{
	if ($logo_text_enabled)
	{

        translate([-20.9,-0.1,0])
    	linear_extrude(h) text("______________", size = size, font = $font_logo_name, halign = "left", $fn = 50);
    
        translate([-20.9,5.3,0])
    	linear_extrude(h) text("______________", size = size, font = $font_logo_name, halign = "left", $fn = 50);
    
		linear_extrude(h) text("COMIXINO", size = size*9/11, font = $font_logo_name, halign = "center", $fn = 50);


	}
}



module base(depth=base_depth){
#difference(){
    half_case(depth=depth, inner=true, base=true);
    conn_side_hole();
    
    #translate([sd_offx, sd_offy,int_support_height+pcb_deep+11.5])
    sd();
    #translate([arduino_offx, arduino_offy,int_support_height+pcb_deep+11.5])
    arduino(); 

 
    //translate([0,0,0])
    #edge_hole(deep=15);
    translate([0,0,-thick_vert])
    #screws_hole();
//translate([0,0,-thick_hor])
}
int_support();

screws_down(depth=int_support_height);
}

module top(depth=12.5){
    difference(){
        translate([0,0,+depth+1*depth_dent]){
        
            scale([1,1,-1])
            half_case(depth=depth,inner=false,base=true);
        }    
        translate([0,0,-(base_deep+joint_dent_offset)])    
        conn_side_hole();
        //conn_up_hole();
        led_hole();
        button_hole();
        screen();
    translate([0,0,+depth+1*depth_dent+thick_vert-0.5])        
    #symbols(deep=0.5);
    
    translate([width*0.465,height*0.85,+depth+1*depth_dent+thick_vert-0.5])        
    #logo();
    

    
    }
    

    
    
//upper screws
#translate([0,0,-joint_dent_offset-1*(base_deep-int_support_height-pcb_deep)])
screws_up(depth=depth+depth_dent+joint_dent_offset+(base_deep-int_support_height-pcb_deep)+0.1, hole=true);


    #translate([0,0,10])
button_hole_tube();

}

base_deep = 5;
//color("#DFDFDF")
base(depth=base_deep);

translate([0,0,base_deep+joint_dent_offset+0])
//color("#DFDFDF")
top();

//buttons();



module buttons(){
button_deep=4.5;
    for(i=[0:1:6]){
        color("#FF6A00")
        translate([button_offx+i*button_deltax,button_offy,int_support_height+pcb_deep+button_deep]){
        button_cap(deep=15, r=button_radius-0.3);   
        }
    }

}
