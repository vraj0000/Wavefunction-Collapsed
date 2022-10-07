#include "Include/Eigen/Core"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
std::vector<unsigned int> intersection(std::vector<unsigned int> v1,
                                      std::vector<unsigned int> v2)
{
    std::vector<unsigned int> v3;

    std::sort(v1.begin(), v1.end());
    std::sort(v2.begin(), v2.end());

    std::set_intersection(v1.begin(),v1.end(),
                          v2.begin(),v2.end(),
                          back_inserter(v3));
    return v3;
}
/**
 * 
 *  i
 * Tile j
 *  |_ Up     k
 *  |   |_ Vectors
 *  |_ Down
 *  |   |_ Vector
 *  |_ Left
 *  |   |_ Vector
 *  |_ Right
 *  |   |_ Vector 
 * blank = 0
 * up = 1   
 * down = 2
 * left = 3
 * right = 4
 */
unsigned int Blank = 0,
            Up =1,
            Down = 2,
            Left = 3,
            Right = 4;
std::vector<std::vector<std::vector<unsigned int>>> DirectionTile
    {
        {{{Blank, Up},{Blank, Down},{Blank, Left},{Blank, Right}}},
        {{{Down, Left, Right},{Blank, Down},{Up,Down,Right},{Up,Down,Left}}},
        {{{Blank, Down},{Up,Left,Right},{Up,Down,Right},{Up,Down,Left}}},
        {{{Down,Left,Right},{Up,Left,Right},{Up,Down,Right},{Blank,Right}}},
        {{{Down,Left,Right},{Up,Left,Right},{Blank,Left},{Up,Down,Left}}}
    };
class Tile
{
    public:

    bool m_Collapsed = false;
    bool m_done = false;
    std::vector<unsigned int> m_Form = {Blank,Up,Down,Left,Right};
    unsigned int m_Entropy = m_Form.size();
    
    Tile()
    {
        //std::cout << m_Form[0] << m_Entropy;
    }
};
class World
{
    private:   
    unsigned int m_Size;
    unsigned int m_NumTile;
    unsigned int m_NumPatterns;
    unsigned int m_Seed;

    public:

    World(unsigned int Size, unsigned int Pattern, unsigned int Cells, unsigned int seed):
    m_Size(Size), m_NumPatterns(Pattern), m_NumTile(Cells), m_Seed(seed)
    {
        // std::cout << "Size of World :-- "<< m_Size << "\n"
        //         << "Number of tiles :-- "<< m_NumTile << "\n"
        //         << "Number of Patterns :-- "<< m_NumPatterns << "\n"; 
    }

    void CreatWorld()
    {
        Tile Zones[m_Size];
        int i,j,k,l = 0, MaxEntropy = 5, SetI, Setj, MaxEntropy2 =5;
        Eigen::Matrix<float,9,9> Matrix9f;
        Matrix9f = Eigen::Matrix<float,9,9>::Zero();
        Eigen::Matrix3f blank = Eigen::Matrix3f::Zero();
        Eigen::Matrix3f up, down, left, right;
        up << 0,1,0,
            1,1,1,
            0,0,0;

        down << 0,0,0,
                1,1,1,
                0,1,0;

        left << 0,1,0,
                1,1,0,
                0,1,0;

        right << 0,1,0,
                0,1,1,
                0,1,0;
        srand(time(0));
        unsigned int RandomPlace = rand() % m_Size;
        srand(14);
        unsigned int RandomTile = rand() % m_NumPatterns;
        Zones[RandomPlace].m_Collapsed = true;
        Zones[RandomPlace].m_Form = {RandomTile};
        Zones[RandomPlace].m_Entropy = 0;
        // std::cout << "\n" << "Random PLace :-- " << RandomPlace << " Randeom Tile :-- " << RandomTile << "\n";
        // std::cout << Zones[RandomPlace].m_Form.size() << " " << Zones[RandomPlace].m_Entropy << "\n";
        MaxEntropy = 5;
        for(i=0; i<m_NumTile; i++)
            for(j=0; j<m_NumTile; j++)
            {
                if (Zones[(i*m_NumTile)+j].m_Entropy < MaxEntropy)
                {
                    MaxEntropy = Zones[(i*m_NumTile)+j].m_Entropy;
                    SetI = i;
                    Setj = j;
                    // std::cout << "Entropy :-" << " " <<Zones[(SetI*m_NumTile)+Setj].m_Entropy << "\n";
                    // std::cout << SetI << " " << Setj << " " << k << "\n";
                }
                
            }
        k=0;
        while (k<8)
        {
        
        for(i=0; i<m_NumTile; i++)
            for(j=0; j<m_NumTile; j++)
            {
                switch (Zones[(i*m_NumTile)+j].m_Form[0])
                {
                    case(0):
                        Matrix9f.block(i*3,j*3,3,3) = blank;
                        break;
                    case(1):
                        Matrix9f.block(i*3,j*3,3,3) = up;
                        break;
                    case(2):
                        Matrix9f.block(i*3,j*3,3,3) = down;
                        break;
                    case(3):
                        Matrix9f.block(i*3,j*3,3,3) = left;
                        break;
                    case(4):
                        Matrix9f.block(i*3,j*3,3,3) = right;
                        break;
                    default:
                        break;
                }
                //std::cout << "Form " << Zones[(i*m_NumTile)+j].m_Entropy << "\n";
                
            }
        // std::cout << "\n" << Matrix9f << "\n";
        // std::cout << "------------------------" << "\n";
        
            
        Zones[(SetI*m_NumTile)+Setj].m_done = true;
        
        // Change the inpofration arround
        // Up
        if(SetI-1 >= 0)
        {
            if(!Zones[((SetI-1)*m_NumTile)+Setj].m_Collapsed)
            {
                Zones[((SetI-1)*m_NumTile)+Setj].m_Form = intersection(Zones[((SetI-1)*m_NumTile)+Setj].m_Form,
                                                            DirectionTile[Zones[(SetI*m_NumTile)+Setj].m_Form[0]][Up-1]);
                Zones[((SetI-1)*m_NumTile)+Setj].m_Entropy = Zones[((SetI-1)*m_NumTile)+Setj].m_Form .size();
                // std::cout << "UP" << Zones[((SetI-1)*m_NumTile)+Setj].m_Entropy<< "\n";
            
            }


        }
        // // Down
        if(SetI+1 < m_NumTile)
        {
            if(!Zones[((SetI+1)*m_NumTile)+Setj].m_Collapsed)
            {
                Zones[((SetI+1)*m_NumTile)+Setj].m_Form = intersection(Zones[((SetI+1)*m_NumTile)+Setj].m_Form,
                                                            DirectionTile[Zones[(SetI*m_NumTile)+Setj].m_Form[0]][Down-1]);
                Zones[((SetI+1)*m_NumTile)+Setj].m_Entropy = Zones[((SetI+1)*m_NumTile)+Setj].m_Form.size();
                // std::cout << "Down" << Zones[((SetI+1)*m_NumTile)+Setj].m_Entropy<< "\n";
            
            }


        }
        // Left
        if(Setj-1 >= 0)
        {
            if(!Zones[((SetI)*m_NumTile)+(Setj-1)].m_Collapsed)
            {
                Zones[((SetI)*m_NumTile)+(Setj-1)].m_Form = intersection(Zones[((SetI)*m_NumTile)+(Setj-1)].m_Form,
                                                            DirectionTile[Zones[(SetI*m_NumTile)+Setj].m_Form[0]][Left-1]);
                Zones[((SetI)*m_NumTile)+(Setj-1)].m_Entropy = Zones[((SetI)*m_NumTile)+(Setj-1)].m_Form.size();
                // std::cout << "Left" << Zones[((SetI)*m_NumTile)+(Setj-1)].m_Entropy<< "\n";

            }

        }

        // Right
        if(Setj+1 < m_NumTile)
        {
            if(!Zones[((SetI)*m_NumTile)+(Setj+1)].m_Collapsed)
            {
                Zones[((SetI)*m_NumTile)+(Setj+1)].m_Form = intersection(Zones[((SetI)*m_NumTile)+(Setj+1)].m_Form,
                                                            DirectionTile[Zones[(SetI*m_NumTile)+Setj].m_Form[0]][Right-1]);
                Zones[((SetI)*m_NumTile)+(Setj+1)].m_Entropy = Zones[((SetI)*m_NumTile)+(Setj+1)].m_Form.size();
                // std::cout << "Right" << Zones[((SetI)*m_NumTile)+(Setj+1)].m_Entropy<< "\n";

            }

        }
        MaxEntropy2 =10;
        for(i=0; i<m_NumTile; i++)
            for(j=0; j<m_NumTile; j++)
            {
                if (Zones[(i*m_NumTile)+j].m_Entropy > 0 && Zones[(i*m_NumTile)+j].m_Entropy < MaxEntropy2)
                {
                    MaxEntropy2 = Zones[(i*m_NumTile)+j].m_Entropy;
                    SetI = i;
                    Setj = j;
                    
                    // std::cout << "Form " << Zones[(i*m_NumTile)+j].m_Form[0] << "\n";
                    // std::cout << "Entropy :-" << " " <<Zones[(SetI*m_NumTile)+Setj].m_Entropy << "\n";
                    // std::cout << SetI << " " << Setj << " " << k << "\n";
                }
                
            }
        srand(time(0)*15.4);
        Zones[(SetI*m_NumTile)+Setj].m_Collapsed = true;
        Zones[(SetI*m_NumTile)+Setj].m_Form = {Zones[(SetI*m_NumTile)+Setj].m_Form[rand() % Zones[(SetI*m_NumTile)+Setj].m_Entropy]};
        Zones[(SetI*m_NumTile)+Setj].m_Entropy = 0;
        
        k++;
        // std::cout << "------------------" << "\n";
        // std::cout << k << "\n" << "-------------------" << "\n";
        }

        
        for(i=0; i<m_NumTile; i++)
            for(j=0; j<m_NumTile; j++)
            {
                switch (Zones[(i*m_NumTile)+j].m_Form[0])
                {
                    case(0):
                        Matrix9f.block(i*3,j*3,3,3) = blank;
                        break;
                    case(1):
                        Matrix9f.block(i*3,j*3,3,3) = up;
                        break;
                    case(2):
                        Matrix9f.block(i*3,j*3,3,3) = down;
                        break;
                    case(3):
                        Matrix9f.block(i*3,j*3,3,3) = left;
                        break;
                    case(4):
                        Matrix9f.block(i*3,j*3,3,3) = right;
                        break;
                    default:
                        break;
                }
                //std::cout << "Form " << Zones[(i*m_NumTile)+j].m_Entropy << "\n";
            }
        
        for(i=0; i<(9); i++)
        {
            for(j = 0; j < 9; j++)
            {
                    if(Matrix9f.coeff(i,j) == 0)
                    {
                        std::cout << 0 << " " << 0 << " " << 0 << "\n";
                    }
                    if(Matrix9f.coeff(i,j) == 1)
                    {
                        std::cout << 255 << " " << 255 << " " << 255 << "\n";
                    }
                
                
            }

        }
        // std::cout << "\n" << Matrix9f(2,4) << "\n";
        // std::cout << "------------------------" << "\n";
    }


};


int main () 
{
    unsigned int size = 9, Patterns = 5, cell = 3;
    int seed=10;
    World w1(size, Patterns, cell,seed);
    w1.CreatWorld();

   


    // Eigen::Matrix<float,12,12> Matrix9f;
    // Matrix9f = Eigen::Matrix<float,12,12>::Zero();
    // std::unordered_map<int,Eigen::Matrix3f> pat;

    // Eigen::Matrix3f blank = Eigen::Matrix3f::Zero();
    // Eigen::Matrix3f up, down, left, right;
    // up << 0,1,0,
    //       1,1,1,
    //       0,0,0;

    // down << 0,0,0,
    //         1,1,1,
    //         0,1,0;

    // left << 0,1,0,
    //         1,1,0,
    //         0,1,0;

    // right << 0,1,0,
    //          0,1,1,
    //          0,1,0;
    // pat[0] = blank;
    // pat[1] = up;
    // pat[2] = down;
    // pat[3] = left;
    // pat[4] = right;

    
    
    
    return 0;
}

