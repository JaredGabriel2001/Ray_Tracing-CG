#include "rtweekend.h"

#include "bvh.h"
#include "camera.h"
#include "constant_medium.h"
#include "hittable_list.h"
#include "material.h"
#include "quad.h"
#include "sphere.h"
#include "texture.h"

void minha_cena_personalizada() {
    hittable_list world;

    // texturas
    auto earth_texture = make_shared<image_texture>("external/earthmap.jpg");
    auto ground_texture = make_shared<image_texture>("external/minecraft.jpg");
    auto dirt_texture = make_shared<image_texture>("external/bloco_solo_minecraft.jpg");
    auto tnt_texture = make_shared<image_texture>("external/tnt.png");
    auto cloud_texture = make_shared<noise_texture>(4);

    // materiais
    auto ground_material = make_shared<lambertian>(ground_texture);
    auto earth_material = make_shared<lambertian>(earth_texture);
    auto dirt_material = make_shared<lambertian>(dirt_texture);
    auto tnt_material = make_shared<lambertian>(tnt_texture);
    auto cloud_material = make_shared<lambertian>(cloud_texture);
    auto solid_red_material = make_shared<lambertian>(color(1.0, 0.1, 0.1));
    auto glass_material = make_shared<dielectric>(1.5);
    auto metal_material = make_shared<metal>(color(0.8, 0.6, 0.2), 0.1);
    auto light_material = make_shared<diffuse_light>(color(7, 7, 7)); // Luz branca

    // objetos-
    world.add(make_shared<quad>(point3(-20,0,-20), vec3(40,0,0), vec3(0,0,40), ground_material));
    world.add(make_shared<sphere>(point3(0, 2, 0), 2, earth_material));
    
    point3 center1 = point3(-4, 0.5, 2);
    point3 center2 = center1 + vec3(1, 0, 0);
    world.add(make_shared<sphere>(center1, center2, 0.5, solid_red_material));

    world.add(box(point3(2, 0, 1), point3(3, 1, 2), dirt_material));
    world.add(box(point3(-1.5, 0, -2), point3(-0.5, 1, -1), tnt_material));

    world.add(make_shared<sphere>(point3(3, 1.2, -1.5), 1.2, cloud_material));
    world.add(make_shared<sphere>(point3(-3, 1.8, -3), 1.8, cloud_material));
    
    world.add(make_shared<sphere>(point3(1, 0.7, 3), 0.7, metal_material));
    world.add(make_shared<sphere>(point3(-2, 0.8, 3.5), 0.8, glass_material));
    
    world.add(make_shared<quad>(point3(-5, 8, -5), vec3(10, 0, 0), vec3(0, 0, 10), light_material));

    world = hittable_list(make_shared<bvh_node>(world));

    // camera
    camera cam;

    cam.aspect_ratio      = 16.0 / 9.0;
    cam.image_width       = 800;
    cam.samples_per_pixel = 200;
    cam.max_depth         = 50;
    cam.background        = color(0, 0, 0);

    /* camera1
    cam.vfov     = 50.0;
    cam.lookfrom = point3(0, 4, 9);
    cam.lookat   = point3(0, 1, 0);
    cam.vup      = vec3(0, 1, 0);
    */
    
    /* camera2
    cam.vfov     = 50.0;
    cam.lookfrom = point3(-9, 4, 0); // Posição 90 graus à ESQUERDA
    cam.lookat   = point3(0, 1, 0);
    cam.vup      = vec3(0, 1, 0);
    */

    /* camera3 
    cam.vfov     = 50.0;
    cam.lookfrom = point3(9, 4, 0); // Posição 90 graus à DIREITA
    cam.lookat   = point3(0, 1, 0);
    cam.vup      = vec3(0, 1, 0);
    */

    /* camera4
    cam.vfov     = 55.0; // Um FOV um pouco mais aberto para a visão de cima
    cam.lookfrom = point3(0, 7, 9);  // MESMA POSIÇÃO XZ do Ângulo 0, mas MUITO MAIS ALTO (Y=7)
    cam.lookat   = point3(0, 0, 0);  // Olhando para o centro do chão
    cam.vup      = vec3(0, 1, 0);    // vup normal funciona perfeitamente aqui
    */

    //camera5
    cam.vfov     = 50.0;
    cam.lookfrom = point3(0, 4, -9); // Posição de TRÁS
    cam.lookat   = point3(0, 1, 0);
    cam.vup      = vec3(0, 1, 0);

    cam.defocus_angle = 0.5;
    cam.focus_dist    = (cam.lookfrom - cam.lookat).length();

    cam.render(world);
}


void random_spheres() { }
void two_spheres() { }
void earth() { }
void two_perlin_spheres() { }
void quads() { }
void simple_light() { }
void cornell_box() { }
void final_scene() { }


int main() {
    minha_cena_personalizada();
}