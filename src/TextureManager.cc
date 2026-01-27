#include "TextureManager.h"
#include "Piece.h"
#include "stb_image.h"

std::unordered_map<Label, const char *> TextureManager::white_texture_filename_map = {
    {Label::PAWN, "../assets/sprites/white_pawn.png"},
    {Label::KNIGHT, "../assets/sprites/white_knight.png"},
    {Label::BISHOP, "../assets/sprites/white_bishop.png"},
    {Label::ROOK, "../assets/sprites/white_rook.png"},
    {Label::QUEEN, "../assets/sprites/white_queen.png"},
    {Label::KING, "../assets/sprites/white_king.png"}};

std::unordered_map<Label, const char *> TextureManager::black_texture_filename_map = {
    {Label::PAWN, "../assets/sprites/black_pawn.png"},
    {Label::KNIGHT, "../assets/sprites/black_knight.png"},
    {Label::BISHOP, "../assets/sprites/black_bishop.png"},
    {Label::ROOK, "../assets/sprites/black_rook.png"},
    {Label::QUEEN, "../assets/sprites/black_queen.png"},
    {Label::KING, "../assets/sprites/black_king.png"}};

std::unordered_map<Label, GLuint> TextureManager::white_textures{};
std::unordered_map<Label, GLuint> TextureManager::black_textures{};

GLuint TextureManager::get(Label label, Color color) {
        if (color == Color::WHITE) {
                auto it = white_textures.find(label);
                if (it == white_textures.end()) {
                        GLuint id = loadTexture(white_texture_filename_map.at(label));
                        it = white_textures.emplace(label, id).first;
                }
                return it->second;
        } else if (color == Color::BLACK) {
                auto it = black_textures.find(label);
                if (it == black_textures.end()) {
                        GLuint id = loadTexture(black_texture_filename_map.at(label));
                        it = black_textures.emplace(label, id).first;
                }
                return it->second;
        }
        return INT_MAX;
}

GLuint TextureManager::loadTexture(const char *filename) {
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
