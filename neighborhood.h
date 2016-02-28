/* ----------------------------------------------------------------------------
* Copyright &copy; 2016 Hunter Straub <Hunterstraub@csu.fullerton.edu>
* Released under the [MIT License] (http://opensource.org/licenses/MIT)
* ------------------------------------------------------------------------- */

#ifndef NEIGHBORHOOD_H
#define NEIGHBORHOOD_H
// ----------------------------------------------------------------------------
#include "constants.h"
#include "shape.h"
#include <chrono>
#include <thread>
// ----------------------------------------------------------------------------

class Shape;

// ----------------------------------------------------------------------------

class Neighborhood {
    private:
        Shape * neighborhood_;

    public:
        const unsigned int size_x = 0;
        const unsigned int size_y = 0;

        Neighborhood(unsigned int size_x, unsigned int size_y);

        ~Neighborhood(){ delete[] neighborhood_; }

    	Shape get(unsigned int x, unsigned int y) const
    	{
    		if( x > TERM_SIZE_X || y > TERM_SIZE_Y)
    		{
    			std::cerr << "Neighborhood::get`: index out of bounds\n";
    			exit(1);
    		}
    		else
    			return neighborhood_[ y * size_x + x];
    	}

    	void set(unsigned int x, unsigned int y, const Shape & s) const
    	{
    		if( x > size_x || y > size_y)
    		{
    			std::cerr << "Neighborhood::set`: index out of bounds\n";
    			exit(1);
    		}
    		else
    			neighborhood_[ y * size_x + x] = s;
    	}

		void move(unsigned int old_x, unsigned int old_y);

        void animate(unsigned int frames){
            
    Buffer b(size_x * Shape::size_x, size_y * Shape::size_y);

    for (; frames; frames--) {
        // draw all the shapes in our neighborhood to it 
        for (int y=0; y < size_y; y++)
            for (int x=0; x < size_x; x++)
                get(x, y).drawToBuffer( b, x * Shape::size_x,
                                           y * Shape::size_y );
                
                b.draw();


                for (int y=0; y < size_y; y++)
	            for (int x=0; x < size_x; x++)
	                if (! get(x, y).isHappy(*this, x, y))
	                   move(x, y);
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        }
};

// ----------------------------------------------------------------------------
#endif
