//
//  Models.cpp
//
//  Assignment-specific code for objects.  This module will typically be
//  heavily modified to fit the needs of each assignment.
//
//  Created by Warren R. Carithers on 2021/09/02.
//  Based on earlier versions created by Joe Geigel and Warren R. Carithers
//  Copyright 2021 Rochester Institute of Technology. All rights reserved.
//
//  Contributor:  Nicholas Shinn
//

#include <iostream>
#include <cmath>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif

#include "Models.h"

//
// PUBLIC GLOBALS
//

// object names (must match the sequence in Models.h)
const char *objects[ N_SHAPES ] = {
    "Cube", "Cone"
};

//
// PRIVATE FUNCTIONS
//

///
/// createCube - Create a unit cube, centered at the origin, with a given
/// number of subdivisions in each direction on each face.
///
/// @param C - the Canvas to use when drawing
/// @param radius - distance of each face from the origin
/// @param factor - number of equal subdivisons to be made in each 
///        direction along each face
///
/// Can only use calls to C.addTriangle()
///
static void createCube( Canvas &C, float radius, int factor )
{
    if( factor < 1 )
        factor = 1;

    // YOUR IMPLEMENTATION HERE
    
    // Sets up an array of vertices to hold the corners of each subdivided square
    Vertex cor[4];

    // Sets up an array of floats to hold the subdivisions of the boundary lines
    float subs[factor+1];

    // Initialize the first element to the lowest possible value
    subs[0] = -radius;

    // Calculates equal subdivisions of the line and translates them to our coordinate system
    for( int i = 1; i < factor; i++ ){
	    subs[i] = ( ( (radius * 2)  / factor ) * i ) - radius;
    }

    //Initializes the last element to the highest possible value
    subs[factor] = radius;

    // Sets up floats to track the bounds of what is essentially the current row and column
    float low;
    float up;
    float rlow;
    float rup;

    // Iteratively grabs the lower and upper bounds defining the current y-coordinate space
    for( int count = 0; count < factor; count++ ){
	low = subs[count];
	up = subs[count+1];

	for(int i = 0; i < factor; i++){

		//Grabs the lower and upper bounds defining the curent x-coordinate space
		rlow = subs[i];
		rup = subs[i+1];

		//Defines the front-facing square using x and y as the coordinate system (z is constant)
		cor[0]= { rlow, low, radius, 0.0 };
		cor[1]= { rup, low, radius, 0.0 };
		cor[2] = { rlow, up, radius, 0.0 };
    		cor[3] = { rup, up, radius, 0.0 };

		// Creates the lower right triangle first followed by the upper left triangle
		C.addTriangle(cor[1], cor[3], cor[0]);
		C.addTriangle(cor[3], cor[2], cor[0]);

		// Changes the z-coordinates to negative radius for drawing the back facing square
		for( int j = 0; j < 4; j++ ){
			cor[j].z = -radius;
		}

		// Creates the triangles, reversing them so they initally face backwards
		C.addTriangle( cor[0], cor[2], cor[1]);
		C.addTriangle( cor[2], cor[3], cor[1]);

		//Defines the top-facing square using x and z as the coordinate system (y is constant)
		cor[0]= { rlow, radius, low, 0.0 };
        	cor[1]= { rup, radius, low, 0.0 };
        	cor[2] = { rlow, radius, up, 0.0 };
        	cor[3] = { rup, radius, up, 0.0 };

		// Creates the triangles
		C.addTriangle( cor[0], cor[2], cor[1]);
        	C.addTriangle( cor[2], cor[3], cor[1]);

		// Changes the y-coordinates to negative radius for drawing bottom-facing square
        	for( int j = 0; j < 4; j++ ){
                	cor[j].y = -radius;
        	}

		// Creates the triangles, reversing them so they initially face downwards
		C.addTriangle(cor[1], cor[3], cor[0]);
        	C.addTriangle(cor[3], cor[2], cor[0]);

		// Defines the left-facing square using z and y as the coordinate system (x is constant)
		cor[0]= { radius, low, rlow, 0.0 };
        	cor[1]= { radius, low, rup, 0.0 };
        	cor[2] = { radius, up, rlow, 0.0 };
        	cor[3] = { radius, up, rup, 0.0 };

		// Creates the triangles
        	C.addTriangle( cor[0], cor[2], cor[1]);
        	C.addTriangle( cor[2], cor[3], cor[1]);

		// Changes the x-coordinates to negative radius for drawing right-facing square
        	for( int j = 0; j < 4; j++ ){
                	 cor[j].x = -radius;
        	}

		// Creates the triangles
		C.addTriangle(cor[1], cor[3], cor[0]);
        	C.addTriangle(cor[3], cor[2], cor[0]);
	}
    }

}

///
/// createCone - Create polygons for a cone with unit height, centered at
/// the origin, with separate number of radial subdivisions and height 
/// subdivisions.
///
/// @param C - the Canvas to use when drawing
/// @param radius - Radius of the base of the cone
/// @param disc - number of subdivisions on the radial base
/// @param height - number of subdivisions along the height
///
/// Can only use calls to C.addTriangle()
///
static void createCone( Canvas &C, float radius, int disc, int height )
{
    if( disc < 3 )
        disc = 3;

    if( height < 1 )
        height = 1;

    // YOUR IMPLEMENTATION HERE
}

//
// PUBLIC FUNCTIONS
//

///
/// Create an object
///
/// @param C      the Canvas we'll be using
/// @param shape  which shape to draw
/// @param rad    object radius
/// @param f1     primary tessellation factor
/// @param f2     secondary tessellation factor
///
void createObject( Canvas &C, Shape shape, float rad, int f1, int f2 )
{
    switch( shape ) {
    default:
        cerr << "Unknown current shape '" << shape
             << "', drawing cube" << endl;
        // FALL THROUGH
    case Cube:
        createCube( C, rad, f1 );
        break;
    case Cone:
        createCone( C, rad, f1, f2 );
        break;
    }
}
