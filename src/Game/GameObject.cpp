#include "Game/GameObject.hpp"
#include "Core/matrix_functions.hpp"

using namespace Game;

GameObject::GameObject()
{
    m_iType = NONE;
    init();
}

GameObject::GameObject(int type) 
    : m_iType(type) 
{ 
    init(); 
}

GameObject::GameObject(const Core::Vector3 &dir, float speed, const Core::Vector3 &pos, int type)
    : m_vDirection3(dir), m_fSpeed(speed), m_vPosition3(pos), m_iType(type)
{
    m_iLifes = 1;

    m_vColor4[0] = 1.f;
    m_vColor4[1] = 0.f;
    m_vColor4[2] = 0.f;
    m_vColor4[3] = 1.f;
            
    m_iImage = -1;
    m_bVisible = true;
}

GameObject::~GameObject()
{
    if(m_iImage > -1)
        glDeleteTextures(1, &m_iImage);
}
    
void GameObject::render()
{
    if(!isVisible())
        return;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glColor4f(1.f, 1.f, 1.f, 1.f);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, m_iImage);
    glBegin(GL_QUADS); //quadrado
        for(unsigned int i = 0; i < m_vVertices.size(); i++)
        {
            Core::Vector3 vec(1);
            vec[0] = (m_vVertices.at(i)+m_vPosition3)(0,0);
            vec[1] = (m_vVertices.at(i)+m_vPosition3)(1,0);
            
            if(m_iImage >= 0)
            {
                if(i == 0)
                    glTexCoord2f(0.f, 0.f);
                else if(i == 1)
                    glTexCoord2f(0.f, 1.f);
                else if(i == 2)
                    glTexCoord2f(1.f, 1.f);
                else if(i == 3)
                    glTexCoord2f(1.f, 0.f);
            }
            glVertex2f(vec[0], vec[1]);
        }
    glEnd();

    onRender();
}

float GameObject::rotateToDir(bool right)
{
    int toRotate = 1;
    if(!right)
        toRotate *= -1;
    Core::Vector3 perp;
    perp = Core::rotate(MY_PI/2.f)*m_vDirection3; //vetor perpendicular ao vetor dire��o.

    Core::Vector3 speed;
    speed = m_vDirection3*m_fSpeed;

    Core::Vector3 sum;
    sum = speed + perp;

    float angle = toRotate*Core::angle(m_vDirection3, Core::unitary(sum))/10.f;
    rotate(angle);

    return angle;
}

void GameObject::accelerate(bool up)
{
    float v = 1;
    if(!up)
        v *= 1/(-7.f);

    setSpeed(getSpeed() + (v*getAcceleration()));
    if(getSpeed() > getMaxSpeed())
        setSpeed(getMaxSpeed());
    else if(getSpeed() < 0.f)
        setSpeed(0.f);
}

void GameObject::initVertices(float width, float height)
{
    Core::Vector3 v1(1);
    v1[0] = width;
    v1[1] = height;

    Core::Vector3 v2(1);
    v2[0] = width;
    v2[1] = -height;

    Core::Vector3 v3(1);
    v3[0] = -width;
    v3[1] = -height;

    Core::Vector3 v4(1);
    v4[0] = -width;
    v4[1] = height;
    
    std::vector<Core::Vector3> *vec = new std::vector<Core::Vector3>();
    vec->push_back(v1);
    vec->push_back(v2);
    vec->push_back(v3);
    vec->push_back(v4);

    setVertices(*vec);
}

void GameObject::rotate(float angle)
{
    if(angle == 0)
        return;
    Core::Matrix3 rot = Core::rotate(angle);

    Core::Vector3 n_dir = m_vDirection3;
    n_dir = rot*n_dir;
    setDirection(n_dir);
    //Como os vertices ja estao em rela��o � origem, n�o precisa transladar para a origem e depois para o lugar certo.
    adjustVertices(rot);
}

float GameObject::rotateTo(Core::Vector2 &dot)
{
    Core::Vector2 dir;
    dir[0] = m_vDirection3[0];
    dir[1] = m_vDirection3[1];

    Core::Vector2 pos;
    pos[0] = m_vPosition3[0];
    pos[1] = m_vPosition3[1];

    dot -= pos;
    dot = Core::unitary(dot);

    dir = Core::translate(pos)*dir;
    dir -= pos;

    dir = Core::unitary(dir);

    std::cout << std::endl << "dot: " << dot[0] << ", " << dot[1] << std::endl;
    std::cout << "dir: " << dir[0] << ", " << dir[1] << std::endl;

    float ang = Core::angle(dir, dot);
    std::cout << "ang: " << ang << std::endl << std::endl;
    if(ang != 0)
    {
        rotate((MY_PI/2.f)/10.f);
    }
    //else if(ang > .3f)
    //    rotate(-.03f);
    return ang;
}