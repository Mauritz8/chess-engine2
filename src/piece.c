#include <stdlib.h>

#include "piece.h"

void piece_array_push(PieceArray* piece_array, const Piece* piece) {
    if (piece_array->length == piece_array->capacity) {
        piece_array->capacity *= 2;
        piece_array->pieces = realloc(piece_array->pieces, piece_array->capacity * sizeof(Piece));
    }
    piece_array->pieces[piece_array->length++] = *piece;
}

char get_char_representation(const Piece_type piece_type) {
    switch (piece_type) {
        case PAWN:
            return 'p';
        case KNIGHT:
            return 'N';
        case BISHOP:
            return 'B';
        case ROOK:
            return 'R';
        case QUEEN:
            return 'Q';
        case KING:
            return 'K';
    }
}

Piece_type get_piece_type(const char char_representation) {
    switch (tolower(char_representation)) {
        case 'p': return PAWN;
        case 'n': return KNIGHT;
        case 'b': return BISHOP;
        case 'r': return ROOK;
        case 'q': return QUEEN;
        case 'k': return KING;
        default: return -1;
    }
}

Piece_type get_promotion_piece_type(const char char_representation_lowercase) {
    if (char_representation_lowercase == 'n') return KNIGHT;
    if (char_representation_lowercase == 'b') return BISHOP;
    if (char_representation_lowercase == 'r') return ROOK;
    if (char_representation_lowercase == 'q') return QUEEN;
    return -1;
}
