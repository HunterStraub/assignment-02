/* ----------------------------------------------------------------------------
* Copyright &copy; 2016 Hunter Straub <Hunterstraub@csu.fullerton.edu>
* Released under the [MIT License] (http://opensource.org/licenses/MIT)
* ------------------------------------------------------------------------- */

#ifndef SHAPE_H
#define SHAPE_H
// ----------------------------------------------------------------------------

#include <string>
#include "buffer.h"
#include "neighborhood.h"

// ----------------------------------------------------------------------------

class Neighborhood;
/
// ----------------------------------------------------------------------------

class Shape {
    private:
        std::string type_;

        std::string type_art_;
        /**
         * The ASCII art representing the type in `type_`.
         *
         * This should be set along with `type_` by the `setType` member
         * function.
         *
         * You may make your own ASCII art for each type, or you may use
         * - empty
         *   ```
"     \n     \n     \n"
         *   ```
         * - triangle
         *   ```
"  ,  \n / \\ \n/___\\\n"
         *   ```
         * - square
         *   ```
".---.\n|   |\n'---'\n"
         *   ```
         *
         * Make sure that the number of rows and columns is the same for each
         * shape, and that it matches `size_x` (for columns) and `size_y` (for
         * rows).
         */

    public:
        static const unsigned int size_x = 5;  // must match actual size
        static const unsigned int size_y = 3;  // must match actual size

	Shape(const std::string & type="empty")
	{
		type_ = type;
		setType(type);
	}

    ~Shape() = default;

    std::string getType() { return type_; }

	void setType(const std::string & type)
	{
		if(type == "empty")
		{
			type_art_ = "     \n"
						 "     \n"
						 "     \n";
		}
		else if(type == "triangle")
		{
			type_art_ = "  ,  \n"
						 " / \\ \n"
						 "/___\\\n";
		}
		else if(type == "square")
		{
			type_art_ = ".---.\n"
						"|   |\n"
						"'---'\n";
		}
		else
		{
			std::cerr << "ERROR: `Shape::setType`: invalid type\n";
			exit(1);
		}
			
	}
    void drawToBuffer(Buffer & b, unsigned int x, unsigned int y) const
	{
		b.set(x,y, type_art_);
	}

    bool isHappy( const Neighborhood & n,
                      unsigned int x,
                      unsigned int y ) const;
};

// ----------------------------------------------------------------------------
#endif

