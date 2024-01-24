//
//
//	uti
//	main.cpp
//

#include <container/vector.hpp>


int main ()
{
        uti::vector vec1d( 4,    1  );
        uti::vector vec2d( 4, vec1d );

        for( uti::ssize_t i = 0; i < 4; ++i )
        {
                for( uti::ssize_t j = 0; j < 4; ++j )
                {
                        std::cout << vec2d.at( i, j ) << " ";
                }
                std::cout << "\n";
        }


        return 0;
}
