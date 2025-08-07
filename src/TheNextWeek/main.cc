#include "rtweekend.h"

#include "bvh.h"
#include "camera.h"
#include "constant_medium.h"
#include "hittable_list.h"
#include "material.h"
#include "quad.h"
#include "sphere.h"
#include "texture.h"

// =================================================================================
// SUA CENA PERSONALIZADA VAI AQUI
// =================================================================================
void minha_cena_personalizada() {
    hittable_list world;

    // --- TEXTURAS ---
    auto earth_texture = make_shared<image_texture>("external/earthmap.jpg");
    auto ground_texture = make_shared<image_texture>("external/minecraft.jpg");
    auto dirt_texture = make_shared<image_texture>("external/bloco_solo_minecraft.jpg");
    auto tnt_texture = make_shared<image_texture>("external/tnt.png");
    auto cloud_texture = make_shared<noise_texture>(4);

    // --- MATERIAIS ---
    auto ground_material = make_shared<lambertian>(ground_texture);
    auto earth_material = make_shared<lambertian>(earth_texture);
    auto dirt_material = make_shared<lambertian>(dirt_texture);
    auto tnt_material = make_shared<lambertian>(tnt_texture);
    auto cloud_material = make_shared<lambertian>(cloud_texture);
    auto solid_red_material = make_shared<lambertian>(color(1.0, 0.1, 0.1));
    auto glass_material = make_shared<dielectric>(1.5);
    auto metal_material = make_shared<metal>(color(0.8, 0.6, 0.2), 0.1);
    auto light_material = make_shared<diffuse_light>(color(7, 7, 7)); // Luz branca

    // --- OBJETOS ---
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

    // Câmera
    camera cam;

    cam.aspect_ratio      = 16.0 / 9.0;
    cam.image_width       = 800;
    cam.samples_per_pixel = 200;
    cam.max_depth         = 50;
    cam.background        = color(0, 0, 0);

    /* --- Câmera  1 centro
    cam.vfov     = 50.0;
    cam.lookfrom = point3(0, 4, 9);
    cam.lookat   = point3(0, 1, 0);
    cam.vup      = vec3(0, 1, 0);
    */
    
    /* --- Câmera 2 (Esquerda) 
    cam.vfov     = 50.0;
    cam.lookfrom = point3(-9, 4, 0); // Posição 90 graus à ESQUERDA
    cam.lookat   = point3(0, 1, 0);
    cam.vup      = vec3(0, 1, 0);
    */

    /* --- Câmera 3 (Direita) 
    cam.vfov     = 50.0;
    cam.lookfrom = point3(9, 4, 0); // Posição 90 graus à DIREITA
    cam.lookat   = point3(0, 1, 0);
    cam.vup      = vec3(0, 1, 0);
    */

    /* --- Câmera 4 (Cima) ---
    cam.vfov     = 55.0; // Um FOV um pouco mais aberto para a visão de cima
    cam.lookfrom = point3(0, 7, 9);  // MESMA POSIÇÃO XZ do Ângulo 0, mas MUITO MAIS ALTO (Y=7)
    cam.lookat   = point3(0, 0, 0);  // Olhando para o centro do chão
    cam.vup      = vec3(0, 1, 0);    // vup normal funciona perfeitamente aqui
    */

    // --- Câmera 5 (Trás) ---
    cam.vfov     = 50.0;
    cam.lookfrom = point3(0, 4, -9); // Posição de TRÁS
    cam.lookat   = point3(0, 1, 0);
    cam.vup      = vec3(0, 1, 0);

    cam.defocus_angle = 0.5;
    cam.focus_dist    = (cam.lookfrom - cam.lookat).length();

    cam.render(world);
}


// =================================================================================
// FUNÇÕES ORIGINAIS DO LIVRO (NÃO MODIFICADAS)
// =================================================================================

void random_spheres() { /* ... código original ... */ }
void two_spheres() { /* ... código original ... */ }
void earth() { /* ... código original ... */ }
void two_perlin_spheres() { /* ... código original ... */ }
void quads() { /* ... código original ... */ }
void simple_light() { /* ... código original ... */ }
void cornell_box() { /* ... código original ... */ }
void final_scene() { /* ... código original ... */ }


int main() {
    minha_cena_personalizada();
}