#include <SDL2/SDL.h>


#include <SDL2/SDL_image.h>

#include <string>
#include <iostream>

#include <vector>

#include <filesystem>


std::string filesystem_find_first_image_file(const std::string &current_working_directory)
{

    SDL_Surface *image = nullptr;
    std::string ret;

    for(auto &p: std::filesystem::directory_iterator(current_working_directory))
    {
        std::cout << p.path() << std::endl;
        std::string file_path = p.path();
        image = IMG_Load(file_path.c_str());
        if(image)
        {
            ret = file_path;

            SDL_FreeSurface(image);
            image = nullptr;

            break;
        }
        else
        {
            std::cout << file_path << " is not a valid image file according to SDL2 IMG lib" << std::endl;
        }
    }

    return ret;
}


std::string filesystem_find_previous_image_file(
    const std::string &current_working_directory,
    const std::string &current_filename
)
{
    SDL_Surface *image = nullptr;
    std::string ret;

    std::vector<std::string> filenames;

    for(auto &p: std::filesystem::directory_iterator(current_working_directory))
    {
        std::cout << p.path() << std::endl;
        std::string file_path = p.path();
        image = IMG_Load(file_path.c_str());
        if(image)
        {
            filenames.push_back(file_path);

            SDL_FreeSurface(image);
            image = nullptr;
        }
        else
        {
            std::cout << file_path << " is not a valid image file according to SDL2 IMG lib" << std::endl;
        }
    }

    std::size_t found_ix = 0;
    for(std::size_t ix = 0; ix < filenames.size(); ++ ix)
    {
        std::string filename = filenames.at(ix);
        if(filename == current_filename)
        {
            if(ix == 0) found_ix = filenames.size() - 1;
            else found_ix = ix - 1;
            break;
        }
    }

    std::string found_filename = filenames.at(found_ix);
    return found_filename;
}


std::string filesystem_find_next_image_file(
    const std::string &current_working_directory,
    const std::string &current_filename
)
{
    SDL_Surface *image = nullptr;
    std::string ret;

    std::vector<std::string> filenames;

    for(auto &p: std::filesystem::directory_iterator(current_working_directory))
    {
        std::cout << p.path() << std::endl;
        std::string file_path = p.path();
        image = IMG_Load(file_path.c_str());
        if(image)
        {
            filenames.push_back(file_path);

            SDL_FreeSurface(image);
            image = nullptr;
        }
        else
        {
            std::cout << file_path << " is not a valid image file according to SDL2 IMG lib" << std::endl;
        }
    }

    std::size_t found_ix = 0;
    for(std::size_t ix = 0; ix < filenames.size(); ++ ix)
    {
        std::string filename = filenames.at(ix);
        if(filename == current_filename)
        {
            if(ix == filenames.size() - 1) found_ix = 0;
            else found_ix = ix + 1;
            break;
        }
    }

    std::string found_filename = filenames.at(found_ix);
    return found_filename;
}


SDL_Surface* SDL_load_image_from_file(const std::string &filename)
{
    SDL_Surface *image = nullptr;

    image = IMG_Load(filename.c_str());
    if(image)
    {

    }
    else
    {
        std::cout << filename << " is not a valid image file according to SDL2 IMG lib" << std::endl;
    }

    return image;
}




void window_resize_to_image(
    SDL_Window *const window,
    const SDL_Surface *const image)
{
    SDL_SetWindowSize(window, image->w, image->h);
    std::cout << "Set window size to " << image->w << " " << image->h << std::endl;
    //SDL_GetWindowSize(window, &rect.w, &rect.h);

    return ;
}


int main(int argc, char* args[])
{


    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not initialize video " << SDL_GetError() << std::endl;
        return 1;
    }
    
    
    //For loading PNG images
    IMG_Init(IMG_INIT_PNG);


    std::string current_working_directory;
    current_working_directory = std::filesystem::current_path();
    std::cout << "current_working_directory=" << current_working_directory << std::endl;

    std::string image_filename; //("test.png");
    image_filename = filesystem_find_first_image_file(current_working_directory);

    SDL_Surface* image = IMG_Load(image_filename.c_str());
    if(image == nullptr)
    {
        std::cout << "Error: Could not load file " << image_filename << std::endl;
    }

    // TODO: duplicate variable
    std::string current_filename = image_filename;





    const int WINDOW_DEFAULT_SIZE_X = 800;
    const int WINDOW_DEFAULT_SIZE_Y = 600;
    int WINDOW_SIZE_X = WINDOW_DEFAULT_SIZE_X;
    int WINDOW_SIZE_Y = WINDOW_DEFAULT_SIZE_Y;

    if(image)
    {
        WINDOW_SIZE_X = image->w;
        WINDOW_SIZE_Y = image->h;
    }

    SDL_Window* window = nullptr;
    window = SDL_CreateWindow("SDL Simple Image Viewer",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        WINDOW_SIZE_X, WINDOW_SIZE_Y,
        SDL_WINDOW_SHOWN);
    if(window == nullptr)
    {
        std::cout << "Error: Could not open window: " << SDL_GetError() << std::endl;
    }
    

    SDL_Renderer* renderer = nullptr;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == nullptr)
    {
        std::cout << "Error: SDL_CreateRenderer " << SDL_GetError() << std::endl;
    }



    // This has to be done after the renderer is initialized, which has to be
    // done after the window is initialzed
    SDL_Texture* texture = nullptr;
    texture = SDL_CreateTextureFromSurface(renderer, image);


    SDL_Rect rect;
    rect.x = 0; //Extreme left of the window
    rect.y = 0; //Very bottom of the window
    //rect.w = 100; //100 pixels width
    //rect.h = 100; //100 pixels height
    //'rect' defines the dimensions for the bottom-left of the window
    SDL_GetWindowSize(window, &rect.w, &rect.h);
    std::cout << "Window Size: " << rect.w << " " << rect.h << std::endl;
    
    SDL_Event event;
    bool quit = false;
    while(!quit)
    {
        while(SDL_PollEvent(&event) > 0)
        {
            if(event.type == SDL_QUIT)
            {
                quit = true;
            }
            else if(event.type == SDL_KEYDOWN)
            {
                if(event.key.keysym.sym == SDLK_q)
                {
                    quit = true;
                }
                else if(event.key.keysym.sym == SDLK_a)
                {
                    window_resize_to_image(window, image);
                }
                else if(event.key.keysym.sym == SDLK_LEFT)
                {
                    std::cout << "Left" << std::endl;

                    current_filename =
                        filesystem_find_previous_image_file(
                            current_working_directory,
                            current_filename);
                    
                    SDL_Surface *new_image = nullptr;
                    new_image = SDL_load_image_from_file(current_filename);
                    // TODO: what happens if file deleted and cannot load
                    // at this point

                    if(new_image)
                    {
                        SDL_FreeSurface(image);
                        image = new_image;
                        new_image = nullptr;

                        SDL_DestroyTexture(texture);
                        texture = nullptr;
                        texture = SDL_CreateTextureFromSurface(renderer, image);
                    }
                }
                else if(event.key.keysym.sym == SDLK_RIGHT)
                {
                    std::cout << "Right" << std::endl;

                    current_filename =
                        filesystem_find_next_image_file(
                            current_working_directory,
                            current_filename);

                    SDL_Surface *new_image = nullptr;
                    new_image = SDL_load_image_from_file(current_filename);
                    // TODO: what happens if file deleted and cannot load
                    // at this point

                    if(new_image)
                    {
                        SDL_FreeSurface(image);
                        image = new_image;
                        new_image = nullptr;

                        SDL_DestroyTexture(texture);
                        texture = nullptr;
                        texture = SDL_CreateTextureFromSurface(renderer, image);
                    }
                }
            }
            else if(event.type == SDL_KEYUP)
            {
                // nothing
            }
        }

        SDL_SetRenderDrawColor(renderer, 80, 80, 80, 255);
        SDL_RenderClear(renderer);

        //Copying the texture on to the window using renderer and rectangle
        SDL_RenderCopy(renderer, texture, NULL, /*&rect*/NULL);

        SDL_RenderPresent(renderer);
    }

    //Deleting the temporary surface
    SDL_FreeSurface(image);

    //Deleting the texture
    SDL_DestroyTexture(texture);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    //For quitting IMG systems
    IMG_Quit();

    SDL_Quit();

    return 0;
}