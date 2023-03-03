#ifndef ENGINE_HPP
# define ENGINE_HPP

#include "event.hpp"
#include "player.hpp"
#include "define.hpp"
#include "mesh.hpp"

#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <map>
#include <algorithm>

struct mat4x4 {
    float m[4][4] = {0};
};

struct Engine {

    Engine(void);
    ~Engine(void);

    int create_window(sf::VideoMode mode, 
                    const std::string &title, 
                    uint32_t style = sf::Style::Default, 
                    const sf::ContextSettings &settings = sf::ContextSettings());

    void    MultiplyMatrixVector(vec3d &i, vec3d &o, mat4x4 &m) {

       	o.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + m.m[3][0];
		o.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + m.m[3][1];
		o.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + m.m[3][2];
		float w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + m.m[3][3];

		if (w != 0.0f)
		{
			o.x /= w; o.y /= w; o.z /= w;
		}
    }

    vec3d   Matrix_MultiplyVector(mat4x4 &m, vec3d &i) {

        vec3d v;

        v.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + i.w * m.m[3][0];
        v.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + i.w * m.m[3][1];
        v.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + i.w * m.m[3][2];
        v.w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + i.w * m.m[3][3];
        return v;
    }

    mat4x4 Matrix_MakeIdentity(void) {

        mat4x4 matrix;
        
        matrix.m[0][0] = 1.0f;
        matrix.m[1][1] = 1.0f;
        matrix.m[2][2] = 1.0f;
        matrix.m[3][3] = 1.0f;
        return matrix;
    }

    mat4x4 Matrix_MakeRotationX(float fAngleRad) {

        mat4x4 matrix;
        
        matrix.m[0][0] = 1.0f;
        matrix.m[1][1] = cos(fAngleRad);
        matrix.m[1][2] = sinf(fAngleRad);
        matrix.m[2][1] = -sinf(fAngleRad);
        matrix.m[2][2] = cosf(fAngleRad);
        matrix.m[3][3] = 1.0f;
        return matrix;
    }

    mat4x4 Matrix_MakeRotationY(float fAngleRad) {

        mat4x4 matrix;

        matrix.m[0][0] = cosf(fAngleRad);
        matrix.m[0][2] = sinf(fAngleRad);
        matrix.m[2][0] = -sinf(fAngleRad);
        matrix.m[1][1] = 1.0f;
        matrix.m[2][2] = cosf(fAngleRad);
        matrix.m[3][3] = 1.0f;
        return matrix;
    }

    mat4x4 Matrix_MakeRotationZ(float fAngleRad) {

        mat4x4 matrix;
        matrix.m[0][0] = cosf(fAngleRad);
        matrix.m[0][1] = sinf(fAngleRad);
        matrix.m[1][0] = -sinf(fAngleRad);
        matrix.m[1][1] = cosf(fAngleRad);
        matrix.m[2][2] = 1.0f;
        matrix.m[3][3] = 1.0f;
        return matrix;
    }

    mat4x4 Matrix_MakeTranslation(float x, float y, float z) {

        mat4x4 matrix;

        matrix.m[0][0] = 1.0f;
        matrix.m[1][1] = 1.0f;
        matrix.m[2][2] = 1.0f;
        matrix.m[3][3] = 1.0f;
        matrix.m[3][0] = x;
        matrix.m[3][1] = y;
        matrix.m[3][2] = z;
        return matrix;
    }

    mat4x4 Matrix_MakeProjection(float fFovDegrees, float fAspectRatio, float fNear, float fFar) {

        float fFovRad = 1.0f / tanf(fFovDegrees * 0.5f / 180.0f * 3.14159f);
        mat4x4 matrix;

        matrix.m[0][0] = fAspectRatio * fFovRad;
        matrix.m[1][1] = fFovRad;
        matrix.m[2][2] = fFar / (fFar - fNear);
        matrix.m[3][2] = (-fFar * fNear) / (fFar - fNear);
        matrix.m[2][3] = 1.0f;
        matrix.m[3][3] = 0.0f;
        return matrix;
    }

    mat4x4 Matrix_MultiplyMatrix(mat4x4 &m1, mat4x4 &m2)
	{
		mat4x4 matrix;
		for (int c = 0; c < 4; c++)
			for (int r = 0; r < 4; r++)
				matrix.m[r][c] = m1.m[r][0] * m2.m[0][c] + m1.m[r][1] * m2.m[1][c] + m1.m[r][2] * m2.m[2][c] + m1.m[r][3] * m2.m[3][c];
		return matrix;
	}

    vec3d Vector_Add(vec3d &v1, vec3d &v2) {

        return { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
    }

    vec3d Vector_Sub(vec3d &v1, vec3d &v2) {

        return { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
    }

    vec3d Vector_Mul(vec3d &v1, float k) {

        return { v1.x * k, v1.y * k, v1.z * k };
    }

    vec3d Vector_Div(vec3d &v1, float k) {

        return { v1.x / k, v1.y / k, v1.z / k };
    }

    float   Vector_DotProduct(vec3d &v1, vec3d &v2) {
        
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    }

    float   Vector_Length(vec3d &v) {
        
        return sqrtf(Vector_DotProduct(v, v));
    }

    vec3d   Vector_Normalise(vec3d &v) {

        float l = Vector_Length(v);
        return { v.x / l, v.y / l, v.z / l};
    }

    vec3d   Vector_CrossProduct(vec3d &v1, vec3d &v2) {

        vec3d v;

        v.x = v1.y * v2.z - v1.z * v2.y;
        v.y = v1.z * v2.x - v1.x * v2.z;
        v.z = v1.x * v2.y - v1.y * v2.x;
        return v;
    }
    bool    onUserCreate(std::string filename) {
        
        mesh    newMesh;
        if (newMesh.LoadObjectFile(filename) == false) {
            std::cerr << "Couldn't load: " << filename << std::endl;
            exit(1);
        }
        objCount++;
        newMesh.name = filename;
        newMesh.id = objCount;
        // Projection Matrix

        matProj = Matrix_MakeProjection((float)FieldOfView, (float)ScreenHeight / (float)ScreenWidth, 0.1f, 1000.0f);
        meshCube.push_back(newMesh);
        return true;
    }

    float   to_radians(float degree) {
        return (degree * (3.14159f / 180));
    }

    bool    onUserUpdate(float fElapsedTime) {
        window.clear();

        if (meshCube.empty()) {
            //currTarget = NULL;
            Targets.clear();
            selectCount = 0;
        }
        for (size_t index = 0; index < meshCube.size(); index++) {
            if (meshCube[index].render == false)
                continue ;
            mat4x4 matRotZ, matRotX, matRotY;

            fTheta = 1.0f * fElapsedTime;

            //matRotZ = Matrix_MakeRotationZ(fTheta * 0.5f);
            matRotZ = Matrix_MakeRotationZ(to_radians(meshCube[index].rot[2]));
            //matRotX = Matrix_MakeRotationX(fTheta);
            matRotY = Matrix_MakeRotationY(to_radians(meshCube[index].rot[1]));
            matRotX = Matrix_MakeRotationX(to_radians(meshCube[index].rot[0]));

            mat4x4 matTrans;
            //matTrans = Matrix_MakeTranslation(0.0f, 0.0f, 5.0f);
            matTrans = Matrix_MakeTranslation(meshCube[index].pos[0], meshCube[index].pos[1], meshCube[index].pos[2]);

            mat4x4 matWorld;
            matWorld = Matrix_MakeIdentity();
            matWorld = Matrix_MultiplyMatrix(matRotZ, matRotX);
            matWorld = Matrix_MultiplyMatrix(matWorld, matRotY);
            matWorld = Matrix_MultiplyMatrix(matWorld, matTrans);
            sf::VertexArray save(sf::LinesStrip, 4);

            std::vector<triangle> TriToRaster;

            for (auto tri: meshCube[index].tris) {
                
                triangle triProjected, triTransformed;

                triTransformed.p[0] = Matrix_MultiplyVector(matWorld, tri.p[0]);
                triTransformed.p[1] = Matrix_MultiplyVector(matWorld, tri.p[1]);
                triTransformed.p[2] = Matrix_MultiplyVector(matWorld, tri.p[2]);

                vec3d normal, line1, line2;

                line1 = Vector_Sub(triTransformed.p[1], triTransformed.p[0]);
                line2 = Vector_Sub(triTransformed.p[2], triTransformed.p[0]);

                normal = Vector_CrossProduct(line1, line2);
                normal = Vector_Normalise(normal);

                vec3d vCameraRay = Vector_Sub(triTransformed.p[0], player.vCam);

                if (Vector_DotProduct(normal, vCameraRay) < 0.0f) {

                    vec3d   light_dir = {0.0f, 1.0f, -1.0f};

                    light_dir = Vector_Normalise(light_dir);

                    float dp = std::max(0.1f, Vector_DotProduct(light_dir, normal));
                    
                    triProjected.color.r = meshCube[index].col[0] * 255 * dp;
                    triProjected.color.g = meshCube[index].col[1] * 255 * dp;
                    triProjected.color.b = meshCube[index].col[2] * 255 * dp;
                    //std::cout << dp << std::endl;

                    triProjected.p[0] = Matrix_MultiplyVector(matProj, triTransformed.p[0]);
                    triProjected.p[1] = Matrix_MultiplyVector(matProj, triTransformed.p[1]);
                    triProjected.p[2] = Matrix_MultiplyVector(matProj, triTransformed.p[2]);

                    triProjected.p[0] = Vector_Div(triProjected.p[0], triProjected.p[0].w);
                    triProjected.p[1] = Vector_Div(triProjected.p[1], triProjected.p[1].w);
                    triProjected.p[2] = Vector_Div(triProjected.p[2], triProjected.p[2].w);
            
                    vec3d vOffsetView = { 1, 1, 0 };

                    triProjected.p[0] = Vector_Add(triProjected.p[0], vOffsetView);
                    triProjected.p[1] = Vector_Add(triProjected.p[1], vOffsetView);
                    triProjected.p[2] = Vector_Add(triProjected.p[2], vOffsetView);

                    triProjected.p[0].x *= 0.5f * (float)ScreenWidth;
                    triProjected.p[0].y *= 0.5f * (float)ScreenHeight;
                    triProjected.p[1].x *= 0.5f * (float)ScreenWidth;
                    triProjected.p[1].y *= 0.5f * (float)ScreenHeight;
                    triProjected.p[2].x *= 0.5f * (float)ScreenWidth;
                    triProjected.p[2].y *= 0.5f * (float)ScreenHeight;

                    TriToRaster.push_back(triProjected);
                }
            }

            std::sort(TriToRaster.begin(), TriToRaster.end(), [](triangle &t1, triangle &t2) {
                    
                float z1 = (t1.p[0].z + t1.p[1].z + t1.p[2].z) / 3.0f;
                float z2 = (t2.p[0].z + t2.p[1].z + t2.p[2].z) / 3.0f;
                return z1 > z2;
            });

            int i = 0;
            for (auto &triProjected: TriToRaster) {
                
                eventloop(window, player);
                if (i && player.part)
                    window.draw(save);
                if (player.part) {
                    save[0].position = sf::Vector2f(triProjected.p[0].x, triProjected.p[0].y);
                    save[1].position = sf::Vector2f(triProjected.p[1].x, triProjected.p[1].y);
                    save[2].position = sf::Vector2f(triProjected.p[2].x, triProjected.p[2].y);
                    save[3].position = sf::Vector2f(triProjected.p[0].x, triProjected.p[0].y);

                    save[0].color = sf::Color::White;
                    save[1].color = sf::Color::White;
                    save[2].color = sf::Color::White;
                    save[3].color = sf::Color::White;
                }
                if (player.part) {
                    
                    sf::VertexArray tmp(sf::LinesStrip, 4);

                    tmp[0].position = sf::Vector2f(triProjected.p[0].x, triProjected.p[0].y);
                    tmp[1].position = sf::Vector2f(triProjected.p[1].x, triProjected.p[1].y);
                    tmp[2].position = sf::Vector2f(triProjected.p[2].x, triProjected.p[2].y);
                    tmp[3].position = sf::Vector2f(triProjected.p[0].x, triProjected.p[0].y);

                    tmp[0].color = sf::Color::Blue;
                    tmp[1].color = sf::Color::Blue;
                    tmp[2].color = sf::Color::Blue;
                    tmp[3].color = sf::Color::Blue;
                    window.draw(tmp);  
                }
                else {

                   /* sf::VertexArray tmp(sf::Triangles, 4);

                    tmp[0].position = sf::Vector2f(triProjected.p[0].x, triProjected.p[0].y);
                    tmp[1].position = sf::Vector2f(triProjected.p[1].x, triProjected.p[1].y);
                    tmp[2].position = sf::Vector2f(triProjected.p[2].x, triProjected.p[2].y);
                    tmp[3].position = sf::Vector2f(triProjected.p[0].x, triProjected.p[0].y);

                    tmp[0].color = triProjected.color;
                    tmp[1].color = triProjected.color;
                    tmp[2].color = triProjected.color;
                    */
                    sf::ConvexShape polygon;

                    polygon.setPointCount(4);
                    polygon.setPoint(0, sf::Vector2f(triProjected.p[0].x, triProjected.p[0].y));
                    polygon.setPoint(1, sf::Vector2f(triProjected.p[1].x, triProjected.p[1].y));
                    polygon.setPoint(2, sf::Vector2f(triProjected.p[2].x, triProjected.p[2].y));
                    polygon.setPoint(3, sf::Vector2f(triProjected.p[0].x, triProjected.p[0].y));
                    polygon.setFillColor(triProjected.color);

                    if (select > 0) {
                        sf::FloatRect boundingBox = polygon.getGlobalBounds();
                        sf::Vector2f mpos = { (float)mouse.x, (float)mouse.y };
                        if (boundingBox.contains(mpos)) {
                            //currTarget = &meshCube[index];
                            if (select == 2) {
                                Targets.erase(meshCube[index].id);
                                meshCube[index].debug = false;
                                selectCount--;
                            }
                            else {
                                Targets[meshCube[index].id] = &meshCube[index];
                                meshCube[index].debug = true;
                                selectCount++;
                            }
                            select = 0;
                        }  
                    }
                    
                    window.draw(polygon);
                    //window.draw(tmp);
                    //if (player.debug) {
                    if (meshCube[index].debug) {

                        sf::VertexArray tmpline(sf::LinesStrip, 4);

                        tmpline[0].position = sf::Vector2f(triProjected.p[0].x, triProjected.p[0].y);
                        tmpline[1].position = sf::Vector2f(triProjected.p[1].x, triProjected.p[1].y);
                        tmpline[2].position = sf::Vector2f(triProjected.p[2].x, triProjected.p[2].y);
                        tmpline[3].position = sf::Vector2f(triProjected.p[0].x, triProjected.p[0].y);

                        tmpline[0].color = sf::Color::Blue;
                        tmpline[1].color = sf::Color::Blue;
                        tmpline[2].color = sf::Color::Blue;
                        tmpline[3].color = sf::Color::Blue;
                        window.draw(tmpline); 
                    }
                }
                i++;
                if (player.part) {
                    std::cout << "i: " << i << std::endl;
                    usleep(500000);
                    window.display();
                }

            }
                
            if (player.part)
                std::cout << std::endl;
        }
        return true;
    }

    sf::RenderWindow window;
    std::string savefile = "save/default.save";
    std::vector<mesh> meshCube;
    Player player;
    mat4x4 matProj;
    float   fTheta;
    sf::Vector2i mouse = {0, 0};
    std::map<std::string, int> count;
    std::map<int, mesh *> Targets;
    int     objCount = 0;
    int     select = 0;
    int     selectCount = 0;
};

#endif
