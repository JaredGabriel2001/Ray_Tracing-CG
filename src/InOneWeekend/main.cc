//==============================================================================================
// Originally written in 2016 by Peter Shirley <ptrshrl@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related and
// neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy (see file COPYING.txt) of the CC0 Public Domain Dedication
// along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
//==============================================================================================

#include "rtweekend.h"

#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"


int main() {
    // cena
    hittable_list world;

    // --- Materiais ---
    auto material_chao = make_shared<metal>(color(0.4, 0.4, 0.4), 0.2);
    auto material_central_metal = make_shared<metal>(color(0.8, 0.8, 0.8), 0.1);
    auto material_metal_dourado = make_shared<metal>(color(0.8, 0.6, 0.2), 0.3);
    auto material_metal_cobre = make_shared<metal>(color(0.8, 0.4, 0.4), 0.5);
    auto material_fosco_azul = make_shared<lambertian>(color(0.1, 0.2, 0.8));
    auto material_reflexivo_topo = make_shared<metal>(color(0.9, 0.9, 0.9), 0.0);

    // --- Objetos ---
    // 1. Chão Metalizado
    world.add(make_shared<sphere>(point3(0,-1000,0), 1000, material_chao));

    // 2. Objetos principais da cena anterior (sem alteração)
    world.add(make_shared<sphere>(point3(0.0, 1.0, 0.0), 1.0, material_central_metal));
    world.add(make_shared<sphere>(point3(-2.0, 0.5, 0.0), 0.5, material_metal_dourado));
    world.add(make_shared<sphere>(point3( 2.0, 0.5, 0.0), 0.5, material_metal_cobre));
    world.add(make_shared<sphere>(point3( 0.0, 0.5, -2.0), 0.5, material_fosco_azul));
    world.add(make_shared<sphere>(point3(0.0, 2.8, 0.0), 0.7, material_reflexivo_topo));

    // 3. 10 esferas pequenas aleatórias (agora mais próximas)
    for (int i = 0; i < 10; ++i) {
        auto radius = random_double(0.1, 0.3);
        // O intervalo de -3 a 3 (em vez de -5 a 5) aproxima as esferas do centro
        point3 center(random_double(-3, 3), radius, random_double(-2.5, 2.5));
        shared_ptr<material> sphere_material;
        auto choose_mat = random_double();

        if (choose_mat < 0.5) {
            sphere_material = make_shared<lambertian>(color::random() * color::random());
        } else if (choose_mat < 0.85) {
            sphere_material = make_shared<metal>(color::random(0.5, 1), random_double(0, 0.5));
        } else {
            sphere_material = make_shared<dielectric>(1.5);
        }
        world.add(make_shared<sphere>(center, radius, sphere_material));
    }

    // 4. Adição de 5 esferas médias metalizadas
    for (int i = 0; i < 5; ++i) {
        auto radius = random_double(0.4, 0.6); // Tamanho médio
        point3 center(random_double(-4, 4), radius, random_double(-3, 3));
        auto albedo = color::random(0.5, 1);
        auto fuzz = random_double(0, 0.3);
        auto sphere_material = make_shared<metal>(albedo, fuzz);
        world.add(make_shared<sphere>(center, radius, sphere_material));
    }

    // 5. Adição de 5 esferas com cores sólidas (foscas)
    for (int i = 0; i < 5; ++i) {
        auto radius = random_double(0.3, 0.5); // Tamanho médio/pequeno
        point3 center(random_double(-4, 4), radius, random_double(-3, 3));
        auto albedo = color::random() * color::random();
        auto sphere_material = make_shared<lambertian>(albedo);
        world.add(make_shared<sphere>(center, radius, sphere_material));
    }


    // Câmera
    camera cam;

    cam.aspect_ratio      = 16.0 / 9.0;
    cam.image_width       = 600;
    cam.samples_per_pixel = 50;
    cam.max_depth         = 20;

    /* CAMERA ORIGINAL
    cam.vfov     = 30;
    cam.lookfrom = point3(13,2,3);
    cam.lookat   = point3(0,0,0);
    cam.vup      = vec3(0,1,0);

    cam.defocus_angle = 0.6;
    cam.focus_dist    = 10.0; */

    /* --- CONFIGURAÇÃO DA CÂMERA 1 ---
    cam.vfov     = 30.0;
    cam.lookfrom = point3(0, 3, 8);  // Posição FRONTAL
    cam.lookat   = point3(0, 1, 0);  // Olhando para a base da esfera central
    cam.vup      = vec3(0, 1, 0); */

    /*--- CONFIGURAÇÃO DA CÂMERA 2 ---
    cam.vfov     = 55.0;
    cam.lookfrom = point3(-8, 4, 0); // Posição 90 graus à ESQUERDA
    cam.lookat   = point3(0, 1, 0);
    cam.vup      = vec3(0, 1, 0); */ 

    /* --- CONFIGURAÇÃO DA CÂMERA 3 ---
    cam.vfov     = 55.0;
    cam.lookfrom = point3(8, 4, 0); // Posição 90 graus à DIREITA
    cam.lookat   = point3(0, 1, 0);
    cam.vup      = vec3(0, 1, 0);
    */

    /* --- CONFIGURAÇÃO DA CÂMERA 4 ---
    cam.vfov     = 55.0;
    cam.lookfrom = point3(0, 10, 0); // Posição de CIMA
    cam.lookat   = point3(0, 1, 0);
    cam.vup      = vec3(0, 0, -1); */

    // --- CONFIGURAÇÃO DA CÂMERA 5 ---
    cam.vfov     = 55.0;
    cam.lookfrom = point3(0, 4, -8); // Posição de TRÁS
    cam.lookat   = point3(0, 1, 0);
    cam.vup      = vec3(0, 1, 0); 

    cam.defocus_angle = 0.2;
    cam.focus_dist    = (cam.lookfrom - cam.lookat).length();

    cam.render(world);
}
