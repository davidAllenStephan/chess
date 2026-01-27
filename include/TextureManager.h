#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include "Piece.h"
#include "stb_image.h"
#include <GLUT/glut.h>
#include <unordered_map>

class TextureManager {
      private:
        static GLuint loadTexture(const char *filename);
        static std::unordered_map<Label, GLuint> white_textures;
        static std::unordered_map<Label, GLuint> black_textures;
        static std::unordered_map<Label, const char *> black_texture_filename_map;
        static std::unordered_map<Label, const char *> white_texture_filename_map;
      public:
        static GLuint get(Label label, Color color);
};

#endif
