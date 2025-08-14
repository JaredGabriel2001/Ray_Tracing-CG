#include "rtweekend.h"

#include "bvh.h"
#include "camera.h"
#include "constant_medium.h"
#include "hittable_list.h"
#include "material.h"
#include "quad.h"
#include "sphere.h"
#include "texture.h"

int main() {
    hittable_list world;
    auto lights = make_shared<hittable_list>();

    // texturas
    auto ground_texture = make_shared<image_texture>("external/minecraft.jpg");
    auto dirt_texture = make_shared<image_texture>("external/bloco_solo_minecraft.jpg");

    // materiais
    auto ground_material = make_shared<lambertian>(ground_texture);
    auto dirt_material = make_shared<lambertian>(dirt_texture);
    
    auto red_material   = make_shared<lambertian>(color(.65, .05, .05));
    auto white_material = make_shared<lambertian>(color(.73, .73, .73));
    auto green_material = make_shared<lambertian>(color(.12, .45, .15));
    auto yellow_material = make_shared<lambertian>(color(0.8, 0.8, 0.1));
    auto metal_material = make_shared<metal>(color(0.8, 0.8, 0.8), 0.1);
    auto glass_material = make_shared<dielectric>(1.5);
    
    auto light = make_shared<diffuse_light>(color(15, 15, 15));

    // objetos

    // 1. Paredes da Cornell Box com chão de Minecraft e fundo amarelo
    world.add(make_shared<quad>(point3(555,0,0), vec3(0,555,0), vec3(0,0,555), green_material)); // Parede Esquerda
    world.add(make_shared<quad>(point3(0,0,0), vec3(0,555,0), vec3(0,0,555), red_material));   // Parede Direita
    world.add(make_shared<quad>(point3(0,0,555), vec3(555,0,0), vec3(0,555,0), yellow_material)); // Parede do Fundo (Amarela)
    world.add(make_shared<quad>(point3(0,555,0), vec3(555,0,0), vec3(0,0,555), white_material)); // Teto
    world.add(make_shared<quad>(point3(0,0,0), vec3(555,0,0), vec3(0,0,555), ground_material));  // Chão (Minecraft)

    // Luz no teto
    auto light_quad = make_shared<quad>(point3(213,554,227), vec3(130,0,0), vec3(0,0,105), light);
    world.add(light_quad);
    lights->add(light_quad);

    // 2. Cubo de Metal (com erro)
    shared_ptr<hittable> metal_box = box(point3(0,0,0), point3(120,120,120), metal_material);
    metal_box = make_shared<rotate_y>(metal_box, 15);
    metal_box = make_shared<translate>(metal_box, vec3(100, 0, 300));
    world.add(metal_box);

    // 3. Duas esferas de vidro pequenas
    world.add(make_shared<sphere>(point3(190, 60, 190), 60, glass_material));
    world.add(make_shared<sphere>(point3(320, 60, 100), 60, glass_material));

    // 4. Cubo médio com textura de Minecraft
    shared_ptr<hittable> dirt_box = box(point3(0,0,0), point3(150,150,150), dirt_material);
    dirt_box = make_shared<rotate_y>(dirt_box, -25);
    dirt_box = make_shared<translate>(dirt_box, vec3(380,0,200));
    world.add(dirt_box);

    // 5. "Triângulo" vermelho (na verdade, uma cunha/rampa fina e rotacionada)
    shared_ptr<hittable> wedge = box(point3(0,0,0), point3(200, 20, 80), red_material);
    wedge = make_shared<rotate_y>(wedge, 20);
    wedge = make_shared<translate>(wedge, vec3(180, 0, 400)); // Posicionado atrás (Z > 300)
    world.add(wedge);
    
    // Otimização final
    world = hittable_list(make_shared<bvh_node>(world));

    // cameara
    camera cam;
    cam.aspect_ratio      = 1.0;
    cam.image_width       = 600;
    cam.samples_per_pixel = 100; // Aumente para 1000+ para a imagem final
    cam.max_depth         = 10;
    cam.background        = color(0,0,0);

    /* camera1
    cam.vfov     = 40.0;
    cam.lookfrom = point3(278, 278, -800);
    cam.lookat   = point3(278, 278, 0);
    cam.vup      = vec3(0,1,0);
    */
    
      /* camera2
    cam.vfov     = 40.0;
    cam.lookfrom = point3(450, 300, -400); 
    cam.lookat   = point3(278, 100, 278);  
    cam.vup      = vec3(0,1,0);
    */

     /*camera3
    cam.vfov     = 60.0;
    cam.lookfrom = point3(450, 50, -200); // Posição baixa (Y=50), na esquerda e à frente
    cam.lookat   = point3(278, 150, 278); // Olhando para cima, em direção ao centro dos objetos
    cam.vup      = vec3(0,1,0);
    */

   /* camera4
    cam.vfov     = 40.0;
    cam.lookfrom = point3(278, 600, -800); // Posição elevada (Y=600) e em frente à caixa
    cam.lookat   = point3(278, 150, 278);  // Olhando para o centro da cena, um pouco acima do chão
    cam.vup      = vec3(0,1,0);
  */
    
  //camera5
    cam.vfov     = 40.0;
    cam.lookfrom = point3(100, 278, 278); // Posição próxima da parede direita (x=0)
    cam.lookat   = point3(278, 0, 278);   // Mirando no centro do chão para inclinar para baixo
    cam.vup      = vec3(0,1,0);
    

    cam.defocus_angle = 0;

    cam.render(world, *lights);
}