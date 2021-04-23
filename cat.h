#ifndef CAT_H
#define CAT_H

#include <iostream>
#include "color.h"
#include "vec2.h"

class cat {
    public:
        cat(int wid = 300, vec2 cen = vec2(300,300), int dep=5, color backC = (color(255, 255, 255))) : width(wid), center(cen), depth(dep), backgroundC(backC){
            center.setY(center.y()-0.2*width);
            calcShapePos();
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
                if (res && obj.getDepth() > curDepth) {
                    inC = obj.getInC();
                    inTrue = true;
                    curDepth = obj.getDepth();
                }
            }
            for (auto obj : bangsFace) {
                res = obj.evalIn(x,y);
                if (res && obj.getDepth() > curDepth) {
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

    void translate(vec2 translation) {
        center += translation;
        calcShapePos();
    }
    double getDepth() {
        return depth;
    }
    vec2 getCen() {
        return center;
    }
    int getWidth() {
        return width;
    }
    void setBackgroundC(color inC) {
        backgroundC = inC;
    }
    private:
        vector<ellipse> face;
        vector<Polygon> hairEyesNose;
        vector<Rect> bangsFace;

        vector<vec2> verticesHair;
        vector<vec2> verticesNose;
        vector<vec2> verticesMouth; // black triangle mouth
        vector<vec2> verticesMouth2; // to cover up the black triangle

        vector<vec2> verticesEyeL;
        vector<vec2> verticesEyeR;

        int depth;
        int width;
        vec2 center;
        color inC;
        color backgroundC;

        // Calculates all the positions of the cat's vertices depending on the private vec2 center
        void calcShapePos() {
            color black = color(0,0,0);
            verticesHair = {vec2(center.x()-width/2, center.y()+width/2),
                                        vec2(center.x()-0.4*width, center.y()+0.1*width), 
                                        vec2(center.x()-0.2*width, center.y()-.1*width),
                                        vec2(center.x()+0.2*width, center.y()-.1*width),
                                        vec2(center.x()+0.4*width, center.y()+0.1*width),
                                        vec2(center.x()+width/2, center.y()+width/2)};
           
            Polygon hair(verticesHair, 1, black);
            hairEyesNose.push_back(hair);

            color faceColor = color(255, 245, 191);
            Rect face1(vec2(center.x()-.25*width, center.y()+.15*width), vec2(center.x()+.25*width, center.y()+.4*width), color(255, 245, 191), 2);
            bangsFace.push_back(face1);

            ellipse face2(vec2(center.x(), center.y() + .4*width), vec2(.25*width, .1*width), 3, faceColor);
            face.push_back(face2);

            color noseColor = color(255, 194, 179);

            
            verticesNose = {  
            vec2(center.x()-0.035*width, center.y()+0.30*width), 
            vec2(center.x()+0.035*width, center.y()+.30*width), 
            vec2(center.x(), center.y()+.34*width)};

            Polygon nose(verticesNose, 4, noseColor);
            hairEyesNose.push_back(nose);

            verticesMouth = {
                vec2(center.x(), center.y()+.35*width),
                vec2(center.x()+0.038*width, center.y()+.39*width),
                vec2(center.x()-0.038*width, center.y()+0.39*width),
            };
            Polygon mouth(verticesMouth, 5, black);
            hairEyesNose.push_back(mouth);

            verticesMouth2 = {
                vec2(center.x(), center.y()+.36*width),
                vec2(center.x()+0.038*width, center.y()+.4*width),
                vec2(center.x()-0.038*width, center.y()+0.4*width),
            };
            Polygon mouth2(verticesMouth2, 6, faceColor);
            hairEyesNose.push_back(mouth2);

            verticesEyeL = {
                vec2(center.x()-.16*width, center.y()+.21*width),
                vec2(center.x()-.06*width, center.y()+.22*width),
                vec2(center.x()-.09*width, center.y()+.26*width)
            };
            Polygon eyeL(verticesEyeL, 7, black);
            hairEyesNose.push_back(eyeL);

            verticesEyeR = {
                vec2(center.x()+.16*width, center.y()+.21*width),
                vec2(center.x()+.09*width, center.y()+.26*width),
                vec2(center.x()+.06*width, center.y()+.22*width)
            };
            Polygon eyeR(verticesEyeR, 8, black);
            hairEyesNose.push_back(eyeR);
        }


};


#endif