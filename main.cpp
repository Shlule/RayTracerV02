#include <iostream>
#include<fstream>
#include"Color.h"
#include"Vec3.h"
#include "Ray.h"

Color rayColor(const Ray& r){
    Vec3 unit_direction = unitVector(r.direction());
    auto t  = 0.5*(unit_direction.y()+1.0);
    return(1.0-t)*Color(1.0,1.0,1.0)+ t*Color(0.5,0.7,1.0);
}

int main(){

    //Image
    const float aspectRatio =16.0/9.0;

    const int imageWidth =400;
    const int imageHeight = static_cast<int>(imageWidth/aspectRatio);

    //camera
    double viewportHeight =2.0;
    double viewportWidth =aspectRatio * viewportHeight;
    double focalLenght =1.0;

    Vec3 origin= Point3(0,0,0);
    Vec3 horizontal = Vec3(viewportWidth,0,0);
    Vec3 vertical = Vec3(0,viewportHeight,0);
    Vec3 lowerLeftCorner = origin - horizontal/2 - vertical/2 - Vec3(0,0,focalLenght);

    std::ofstream output;

    output.open("output.ppm");
    

    //render

    output<<"P3\n"<<imageWidth<<' '<<imageHeight<<"\n255\n";

    for(int j =imageHeight-1; j>=0; j--){
        std::cerr<<"\rScanlines remaining:" <<j<<' '<<std::flush;
        for(int i=0; i<imageWidth; i++ ){
            double u =double(i)/(imageWidth-1);
            double v =double(j)/(imageHeight-1);
            //mon Ray r a besoin d'une origine et d'une diurection
            Ray r(origin, lowerLeftCorner+u*horizontal+v*vertical-origin);
            Color pixelColor = rayColor(r);
            writeColor(output, pixelColor);

        }
    }
    std::cerr<<"\n Done. \n";
    output.close();
    return 0;
}

