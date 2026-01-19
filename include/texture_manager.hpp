#include "stb_image.h"
#include <GLUT/glut.h>
#include <unordered_map>

inline GLuint LoadTexture(const char *filename) {
        int width, height, channels;
        unsigned char *data = stbi_load(filename, &width, &height, &channels, 4);
        if (!data) {
                fprintf(stderr, "Failed to load image: %s\n", filename);
                return 0;
        }
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        stbi_image_free(data);
        return texture;
}

enum TEXTURE {
        WHITE_PAWN,
        WHITE_KNIGHT,
        WHITE_BISHOP,
        WHITE_ROOK,
        WHITE_QUEEN,
        WHITE_KING,
        BLACK_PAWN,
        BLACK_KNIGHT,
        BLACK_BISHOP,
        BLACK_ROOK,
        BLACK_QUEEN,
        BLACK_KING
};

inline std::unordered_map<TEXTURE, const char *> texture_filename_map = {
    {WHITE_PAWN, "../assets/white_pawn.png"},
    {WHITE_KNIGHT, "../assets/white_knight.png"},
    {WHITE_BISHOP, "../assets/white_bishop.png"},
    {WHITE_ROOK, "../assets/white_rook.png"},
    {WHITE_QUEEN, "../assets/white_queen.png"},
    {WHITE_KING, "../assets/white_king.png"},
    {BLACK_PAWN, "../assets/black_pawn.png"},
    {BLACK_KNIGHT, "../assets/black_knight.png"},
    {BLACK_BISHOP, "../assets/black_bishop.png"},
    {BLACK_ROOK, "../assets/black_rook.png"},
    {BLACK_QUEEN, "../assets/black_queen.png"},
    {BLACK_KING, "../assets/black_king.png"}

};

class texture_manager {
      public:
        static GLuint getOrLoad(TEXTURE texture) {
                static std::unordered_map<TEXTURE, GLuint> textures;

                auto it = textures.find(texture);
                if (it == textures.end()) {
                        GLuint id = LoadTexture(texture_filename_map.at(texture));
                        it = textures.emplace(texture, id).first;
                }
                return it->second;
        }
};
