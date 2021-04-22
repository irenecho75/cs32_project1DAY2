#ifndef CAT_H
#define CAT_H

#include <iostream>
#include "color.h"
#include "vec2.h"

class cat {
    public:
        cat(int wid = 300, vec2 cen = vec2(100,100), int dep=5, color backC = (color(255, 255, 255))) : width(wid), height(wid), center(cen), depth(dep), backgroundC(backC){
            color black = color(0,0,0);
            vector<vec2> verticesHair = {vec2(cen.x()-width/2, cen.y()+width/2),
                                        vec2(cen.x()-0.4*width, cen.y()+0.1*width), 
                                        vec2(cen.x()-0.2*width, cen.y()+width/2),
                                        vec2(cen.x()+width/2, cen.y()+width/2),
                                        vec2(cen.x()+0.4*width, cen.y()+0.1*width), 
                                        vec2(cen.x()+0.2*width, cen.y()+width/2)};
            Polygon hair(verticesHair, 1, black);
            hairEyesNose.push_back(hair);

        }
        color eval(int x, int y, color backgroundC) {
            float res;
            color inC;
            bool inTrue = false;
            double curDepth = -1.0;
            for (auto obj : face) {
                res = obj.eval(x,y);
                if (res < 0 && obj.getDepth() > curDepth) {
                    inC = obj.getInC();
                    inTrue = true;
                    curDepth = obj.getDepth();
                }
            }
            for (auto obj : hairEyesNose) {
                res = obj.eval(x,y);
                if (res < 0 && obj.getDepth() > curDepth) {
                    inC = obj.getInC();
                    inTrue = true;
                    curDepth = obj.getDepth();
                }
            }
            for (auto obj : bangs) {
                res = obj.evalIn(x,y);
                if (res < 0 && obj.getDepth() > curDepth) {
                    inC = obj.getInC();
                    inTrue = true;
                    curDepth = obj.getDepth();
                }
            }

            if (inTrue) {
                return inC;
            }
            else
                return backgroundC;
        }
    private:
        vector<ellipse> face;
        vector<Polygon> hairEyesNose;
        vector<Rect> bangs;
        int depth;
        int width;
        int height;
        vec2 center;
        color inC;
        color backgroundC;


};


#endif