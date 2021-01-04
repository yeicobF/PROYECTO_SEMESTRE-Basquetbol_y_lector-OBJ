/*
 *  Bouncing Ellipse.cpp
 *  C++ First Programming
 *
 *  Draw a ellipse that bouce inside the canvas.
 *
 *  Created by Kape_01 on 5/30/16.
 *  Copyright © 2016 Kapes17. All rights reserved.
 *
 * http://www.cplusplus.com/forum/beginner/192045/
 */

#include <iostream>
#include <math.h>
using namespace std;

int width = 80;
int height = 80; //Canvas size
int ballX = 40; //Ellipse x-axis
int ballY = 40; //Ellipse y-axis
int forceX = 1; //Change the direction of ellipse
int forceY = 1;

int distance(int x1, int y1, int x2, int y2){
    int xDelta = x1 - x2;
    int yDelta = y1 - y2;
    return sqrt(xDelta * xDelta + yDelta * yDelta); //Calculate the half radius of the ellipse
}

void updatePhysics(){
    if(ballX > width - 2 || ballX < 0){ //Keep the ellipse inside the canvas
        forceX = -forceX; //Change the direction
    }
        //Keep bouncing
        ballX += forceX;
        ballY += forceY;
}

void drawFrame(){
    for(int y = 0; y < height; y ++){
        for(int x = 0; x < width; x ++){

            if(distance(x, y * 2, ballX, ballY) < 4){
                cout << ' ';
            }else if(distance(x, y * 2, ballX, ballY) >= 4){
                cout << "x";
            }
        }
        cout << endl;

    }
}

int main(){
    while (true) {
        updatePhysics();
        drawFrame();
    }

    return 0;
}
