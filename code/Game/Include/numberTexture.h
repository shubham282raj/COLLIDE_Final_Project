    #include"SDL.h"

    class numberTextureClass{
        public:
        SDL_Texture* number[10];
        int numberArray[5]={-1};
        int wid=40;
        int hei=70;
        int x = 50;
        int y = 50;
        void loadTexture(SDL_Renderer* renderer){
            SDL_Surface* image = SDL_LoadBMP("Images/numbers/zero.bmp");
            number[0] = SDL_CreateTextureFromSurface(renderer, image);
            image = SDL_LoadBMP("Images/numbers/one.bmp");
            number[1] = SDL_CreateTextureFromSurface(renderer, image);
            image = SDL_LoadBMP("Images/numbers/two.bmp");
            number[2] = SDL_CreateTextureFromSurface(renderer, image);
            image = SDL_LoadBMP("Images/numbers/three.bmp");
            number[3] = SDL_CreateTextureFromSurface(renderer, image);
            image = SDL_LoadBMP("Images/numbers/four.bmp");
            number[4] = SDL_CreateTextureFromSurface(renderer, image);
            image = SDL_LoadBMP("Images/numbers/five.bmp");
            number[5] = SDL_CreateTextureFromSurface(renderer, image);
            image = SDL_LoadBMP("Images/numbers/six.bmp");
            number[6] = SDL_CreateTextureFromSurface(renderer, image);
            image = SDL_LoadBMP("Images/numbers/seven.bmp");
            number[7] = SDL_CreateTextureFromSurface(renderer, image);
            image = SDL_LoadBMP("Images/numbers/eight.bmp");
            number[8] = SDL_CreateTextureFromSurface(renderer, image);
            image = SDL_LoadBMP("Images/numbers/nine.bmp");
            number[9] = SDL_CreateTextureFromSurface(renderer, image);
        }
        void updateNumberArray(int n){
            for(int i=0; i<5; i++){
                numberArray[i]=-1;
            }
            int counter=4;
            while(n!=0){
                numberArray[counter--] = n % 10;
                n/=10;
            }
        }
        void renderNumber(SDL_Renderer* renderer){
            int j=0;
            for(int i=0; i<5; i++){
                if(numberArray[i] != -1){
                    SDL_Rect fillRect = {x+(wid+10)*j, y, wid, hei};
                    SDL_RenderCopy(renderer, number[numberArray[i]], NULL, &fillRect);
                    j++;
                }
            }
        }
    };