#include "chess/ChessState.hpp"

// Static variable definitions
Bitboard ChessState::s_ROOK_MASKS[64] = {};
Bitboard ChessState::s_BISHOP_MASKS[64] = {};
Bitboard ChessState::s_ROOK_ATTACKS[64][4096] = {};
Bitboard ChessState::s_BISHOP_ATTACKS[64][512] = {};
bool ChessState::isAttacksInitialized = false;

// Constant array for lookups
const int c_BISHOP_INDEX_BITS[64] = {
	6, 5, 5, 5, 5, 5, 5, 6,
	5, 5, 5, 5, 5, 5, 5, 5,
	5, 5, 7, 7, 7, 7, 5, 5,
	5, 5, 7, 9, 9, 7, 5, 5,
	5, 5, 7, 9, 9, 7, 5, 5,
	5, 5, 7, 7, 7, 7, 5, 5,
	5, 5, 5, 5, 5, 5, 5, 5,
	6, 5, 5, 5, 5, 5, 5, 6
};
const int c_ROOK_INDEX_BITS[64] = {
	12, 11, 11, 11, 11, 11, 11, 12,
	11, 10, 10, 10, 10, 10, 10, 11,
	11, 10, 10, 10, 10, 10, 10, 11,
	11, 10, 10, 10, 10, 10, 10, 11,
	11, 10, 10, 10, 10, 10, 10, 11,
	11, 10, 10, 10, 10, 10, 10, 11,
	11, 10, 10, 10, 10, 10, 10, 11,
	12, 11, 11, 11, 11, 11, 11, 12
};
const U64 c_ROOK_MAGICS[64] = {
	0x8a80104000800020ULL,
	0x140002000100040ULL,
	0x2801880a0017001ULL,
	0x100081001000420ULL,
	0x200020010080420ULL,
	0x3001c0002010008ULL,
	0x8480008002000100ULL,
	0x2080088004402900ULL,
	0x800098204000ULL,
	0x2024401000200040ULL,
	0x100802000801000ULL,
	0x120800800801000ULL,
	0x208808088000400ULL,
	0x2802200800400ULL,
	0x2200800100020080ULL,
	0x801000060821100ULL,
	0x80044006422000ULL,
	0x100808020004000ULL,
	0x12108a0010204200ULL,
	0x140848010000802ULL,
	0x481828014002800ULL,
	0x8094004002004100ULL,
	0x4010040010010802ULL,
	0x20008806104ULL,
	0x100400080208000ULL,
	0x2040002120081000ULL,
	0x21200680100081ULL,
	0x20100080080080ULL,
	0x2000a00200410ULL,
	0x20080800400ULL,
	0x80088400100102ULL,
	0x80004600042881ULL,
	0x4040008040800020ULL,
	0x440003000200801ULL,
	0x4200011004500ULL,
	0x188020010100100ULL,
	0x14800401802800ULL,
	0x2080040080800200ULL,
	0x124080204001001ULL,
	0x200046502000484ULL,
	0x480400080088020ULL,
	0x1000422010034000ULL,
	0x30200100110040ULL,
	0x100021010009ULL,
	0x2002080100110004ULL,
	0x202008004008002ULL,
	0x20020004010100ULL,
	0x2048440040820001ULL,
	0x101002200408200ULL,
	0x40802000401080ULL,
	0x4008142004410100ULL,
	0x2060820c0120200ULL,
	0x1001004080100ULL,
	0x20c020080040080ULL,
	0x2935610830022400ULL,
	0x44440041009200ULL,
	0x280001040802101ULL,
	0x2100190040002085ULL,
	0x80c0084100102001ULL,
	0x4024081001000421ULL,
	0x20030a0244872ULL,
	0x12001008414402ULL,
	0x2006104900a0804ULL,
	0x1004081002402ULL,
};
const U64 c_BISHOP_MAGICS[64] = {
	0x40040844404084ULL,
	0x2004208a004208ULL,
	0x10190041080202ULL,
	0x108060845042010ULL,
	0x581104180800210ULL,
	0x2112080446200010ULL,
	0x1080820820060210ULL,
	0x3c0808410220200ULL,
	0x4050404440404ULL,
	0x21001420088ULL,
	0x24d0080801082102ULL,
	0x1020a0a020400ULL,
	0x40308200402ULL,
	0x4011002100800ULL,
	0x401484104104005ULL,
	0x801010402020200ULL,
	0x400210c3880100ULL,
	0x404022024108200ULL,
	0x810018200204102ULL,
	0x4002801a02003ULL,
	0x85040820080400ULL,
	0x810102c808880400ULL,
	0xe900410884800ULL,
	0x8002020480840102ULL,
	0x220200865090201ULL,
	0x2010100a02021202ULL,
	0x152048408022401ULL,
	0x20080002081110ULL,
	0x4001001021004000ULL,
	0x800040400a011002ULL,
	0xe4004081011002ULL,
	0x1c004001012080ULL,
	0x8004200962a00220ULL,
	0x8422100208500202ULL,
	0x2000402200300c08ULL,
	0x8646020080080080ULL,
	0x80020a0200100808ULL,
	0x2010004880111000ULL,
	0x623000a080011400ULL,
	0x42008c0340209202ULL,
	0x209188240001000ULL,
	0x400408a884001800ULL,
	0x110400a6080400ULL,
	0x1840060a44020800ULL,
	0x90080104000041ULL,
	0x201011000808101ULL,
	0x1a2208080504f080ULL,
	0x8012020600211212ULL,
	0x500861011240000ULL,
	0x180806108200800ULL,
	0x4000020e01040044ULL,
	0x300000261044000aULL,
	0x802241102020002ULL,
	0x20906061210001ULL,
	0x5a84841004010310ULL,
	0x4010801011c04ULL,
	0xa010109502200ULL,
	0x4a02012000ULL,
	0x500201010098b028ULL,
	0x8040002811040900ULL,
	0x28000010020204ULL,
	0x6000020202d0240ULL,
	0x8918844842082200ULL,
	0x4010011029020020ULL,
};
const U64 FILE_H = 0x8080808080808080ull;
const U64 FILE_G = 0x4040404040404040ull;
const U64 FILE_B = 0x202020202020202ull;
const U64 FILE_A = 0x101010101010101ull;
const enum Positions {
	a8, b8, c8, d8, e8, f8, g8, h8,
	a7, b7, c7, d7, e7, f7, g7, h7,
	a6, b6, c6, d6, e6, f6, g6, h6,
	a5, b5, c5, d5, e5, f5, g5, h5,
	a4, b4, c4, d4, e4, f4, g4, h4,
	a3, b3, c3, d3, e3, f3, g3, h3,
	a2, b2, c2, d2, e2, f2, g2, h2,
	a1, b1, c1, d1, e1, f1, g1, h1
};
const enum Castling { wk = 1, wq = 2, bk = 4, bq = 8 };
const int c_CASTLING_RIGHTS[64] = {
	 7, 15, 15, 15,  3, 15, 15, 11,
	15, 15, 15, 15, 15, 15, 15, 15,
	15, 15, 15, 15, 15, 15, 15, 15,
	15, 15, 15, 15, 15, 15, 15, 15,
	15, 15, 15, 15, 15, 15, 15, 15,
	15, 15, 15, 15, 15, 15, 15, 15,
	15, 15, 15, 15, 15, 15, 15, 15,
	13, 15, 15, 15, 12, 15, 15, 14
};
U64 nonSlidingAttacks[ChessState::c_PIECES_AMOUNT][64];

ChessState::ChessState(std::string fen)
{
	int square = 0;
	int index;
	for (index = 0; index < fen.size() && fen[index] != ' '; index++) {
		if (fen[index] == '/') continue;

		if (fen[index] >= '1' && fen[index] <= '8') {
			square += fen[index] - '1';
		}

		switch (fen[index]) {
		case 'P':
			this->bitboards[Pieces::P].setBit(square);
			break;
		case 'R':
			this->bitboards[Pieces::R].setBit(square);
			break;
		case 'B':
			this->bitboards[Pieces::B].setBit(square);
			break;
		case 'N':
			this->bitboards[Pieces::N].setBit(square);
			break;
		case 'Q':
			this->bitboards[Pieces::Q].setBit(square);
			break;
		case 'K':
			this->bitboards[Pieces::K].setBit(square);
			break;
		case 'p':
			this->bitboards[Pieces::p].setBit(square);
			break;
		case 'r':
			this->bitboards[Pieces::r].setBit(square);
			break;
		case 'b':
			this->bitboards[Pieces::b].setBit(square);
			break;
		case 'n':
			this->bitboards[Pieces::n].setBit(square);
			break;
		case 'q':
			this->bitboards[Pieces::q].setBit(square);
			break;
		case 'k':
			this->bitboards[Pieces::k].setBit(square);
			break;
		}

		square++;
	}

	index++;

	if (fen[index] == 'b')
		this->side_ = Color::Black;
	else
		this->side_ = Color::White;

	index += 2;

	this->castle_ = 0;
	while (fen[index] != ' ') {
		switch (fen[index])
		{
		case 'K': this->castle_ |= wk; break;
		case 'Q': this->castle_ |= wq; break;
		case 'k': this->castle_ |= bk; break;
		case 'q': this->castle_ |= bq; break;
		case '-': break;
		}

		// increment pointer to FEN string
		index++;
	}

	index++;

	if (fen[index] != '-')
	{
		// parse enpassant file & rank
		int file = fen[index] - 'a';
		int rank = 8 - (fen[index+1] - '0');

		// init enpassant square
		this->enpassant_ = rank * 8 + file;
	}

	// no enpassant square
	else
		this->enpassant_ = 0ULL;

	if (!this->isAttacksInitialized) {
		this->isAttacksInitialized = true;

		// Initialize rook and bishop attack array
		this->initializeSliderAttacks();
		this->initializeNonSliderAttacks();
	}

	this->generateOccupancyBoards();
}

void ChessState::displayState()
{
	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			int piece = 0;
			int square = row * 8 + col;

			for (int index = 0; index < this->c_PIECES_AMOUNT; index++) {
				if (this->bitboards[index].getBit(square)) {
					piece = index + 1;
					break;
				}
			}
			std::cout << piece << "\t";
		}
		std::cout << std::endl;
	}
}

std::string ChessState::toFEN()
{
	std::string fen = "";
	int counter = 0;
	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			int piece = -1;
			int square = row * 8 + col;

			for (int index = 0; index < this->c_PIECES_AMOUNT; index++) {
				if (this->bitboards[index].getBit(square)) {
					piece = index;
					break;
				}
			}

			if (counter > 0 && piece != -1) {
				fen += std::to_string(counter);
				counter = 0;
			}

			switch (piece) {
			case Pieces::P: fen += 'P';
				break;
			case Pieces::R: fen += 'R';
				break;
			case Pieces::B: fen += 'B';
				break;
			case Pieces::N: fen += 'N';
				break;
			case Pieces::Q: fen += 'Q';
				break;
			case Pieces::K: fen += 'K';
				break;
			case Pieces::p: fen += 'p';
				break;
			case Pieces::r: fen += 'r';
				break;
			case Pieces::b: fen += 'b';
				break;
			case Pieces::n: fen += 'n';
				break;
			case Pieces::q: fen += 'q';
				break;
			case Pieces::k: fen += 'k';
				break;
			default:
				counter++;
			}
		}

		if (counter > 0) {
			fen += std::to_string(counter);
			counter = 0;
		}

		if (row + 1 < 8) fen += '/';
	}

	return fen;
}

U64* ChessState::getOccupancyBoards()
{
	return this->occupancies_;
}

void ChessState::initializeSliderAttacks()
{
	for (int square = 0; square < 64; square++) {
		this->s_BISHOP_MASKS[square] = this->generateBishopAttackMask(square);
		this->s_ROOK_MASKS[square] = this->generateRookAttackMask(square);

		int bishopCounts = this->s_BISHOP_MASKS[square].countBits();
		int rookCounts = this->s_ROOK_MASKS[square].countBits();

		int bishopOccupancyIndex = (1 << bishopCounts);
		int rookOccupancyIndex = (1 << rookCounts);

		// Loop to generate possible moves for bishop at square
		for (int index = 0; index < bishopOccupancyIndex; index++) {
			Bitboard occupancy = this->setOccupancy(index, bishopCounts, this->s_BISHOP_MASKS[square]);
			U64 magicIndex = (occupancy.getBoard() * c_BISHOP_MAGICS[square]) >> (64 - c_BISHOP_INDEX_BITS[square]);
			this->s_BISHOP_ATTACKS[square][magicIndex] = getBishopAttacksSlow(square, occupancy);
		}

		// Loop to generate possible moves for bishop at square
		for (int index = 0; index < rookOccupancyIndex; index++) {
			Bitboard occupancy = this->setOccupancy(index, rookCounts, this->s_ROOK_MASKS[square]);
			U64 magicIndex = (occupancy.getBoard() * c_ROOK_MAGICS[square]) >> (64 - c_ROOK_INDEX_BITS[square]);
			this->s_ROOK_ATTACKS[square][magicIndex] = getRookAttacksSlow(square, occupancy);
		}
	}
}

void ChessState::initializeNonSliderAttacks()
{
	for (int i = 0; i < 64; i++) {
		U64 start = 1ULL << i;

		// Get king attack mask from square 'i'
		U64 attackKing = (((start << 7) | (start >> 9) | (start >> 1)) & (~FILE_H)) |
			(((start << 9) | (start >> 7) | (start << 1)) & (~FILE_A)) |
			((start >> 8) | (start << 8));

		// Get knight attack masks from square 'i'
		U64 attackKnights = (((start << 10) | (start >> 6)) & ~(FILE_A | FILE_B)) |
			(((start >> 10) | (start << 6)) & ~(FILE_H | FILE_G)) |
			(((start << 17) | (start >> 15)) & ~(FILE_A)) |
			(((start >> 17) | (start << 15)) & ~(FILE_H));

		// Get pawn attack masks from square 'i'
		U64 attackPawnW = ((start >> 7) & ~FILE_A) | ((start >> 9) & ~FILE_H);
		U64 attackPawnB = ((start << 7) & ~FILE_H) | ((start << 9) & ~FILE_A);

		nonSlidingAttacks[Pieces::K][i] = attackKing;
		nonSlidingAttacks[Pieces::k][i] = attackKing;

		nonSlidingAttacks[Pieces::N][i] = attackKnights;
		nonSlidingAttacks[Pieces::n][i] = attackKnights;

		nonSlidingAttacks[Pieces::P][i] = attackPawnW;
		nonSlidingAttacks[Pieces::p][i] = attackPawnB;
	}
}

bool ChessState::isSquareAttacked(int square, Color side)
{
	// attacked by black pawns
	if ((side == Color::White) && (nonSlidingAttacks[Pieces::p][square] & this->bitboards[Pieces::P].getBoard())) return true;

	// attacked by white pawns
	U64 t2 = this->bitboards[Pieces::p].getBoard();
	U64 t1 = nonSlidingAttacks[Pieces::P][square];
	U64 blackPawnBoard = t1 & t2;
	if ((side == Color::Black) && blackPawnBoard) return true;

	// attacked by knights
	U64 knightBoard = (side == Color::White ? this->bitboards[N].getBoard() : this->bitboards[n].getBoard());
	if (nonSlidingAttacks[Pieces::N][square] & knightBoard) return true;

	// attacked by bishops
	U64 bishopBoard = ((side == Color::White) ? this->bitboards[B].getBoard() : this->bitboards[b].getBoard());
	if (this->getBishopAttacks(square, this->occupancies_[Color::Both]).getBoard() & bishopBoard) return true;

	// attacked by rooks
	U64 rookBoard = ((side == Color::White) ? this->bitboards[R].getBoard() : this->bitboards[r].getBoard());
	if (this->getRookAttacks(square, this->occupancies_[Color::Both]).getBoard() & rookBoard) return true;

	// attacked by Queens
	U64 queenBoard = ((side == Color::White) ? this->bitboards[Q].getBoard() : this->bitboards[q].getBoard());
	if (this->getQueenAttacks(square, this->occupancies_[Color::Both]).getBoard() & queenBoard) return true;

	// attacked by kings
	U64 kingBoard = ((side == Color::White) ? this->bitboards[K].getBoard() : this->bitboards[k].getBoard());
	if (nonSlidingAttacks[Pieces::K][square] & kingBoard) return true;

	// by default return false
	return false;
}

Bitboard ChessState::getBishopAttacksSlow(int square, Bitboard block)
{
	// result attacks bitboard
	U64 attacks = 0ULL;

	// init ranks & files
	int r, f;

	// init target rank & files
	int tr = square / 8;
	int tf = square % 8;

	// generate bishop atacks
	for (r = tr + 1, f = tf + 1; r <= 7 && f <= 7; r++, f++)
	{
		attacks |= (1ULL << (r * 8 + f));
		if ((1ULL << (r * 8 + f)) & block.getBoard()) break;
	}

	for (r = tr - 1, f = tf + 1; r >= 0 && f <= 7; r--, f++)
	{
		attacks |= (1ULL << (r * 8 + f));
		if ((1ULL << (r * 8 + f)) & block.getBoard()) break;
	}

	for (r = tr + 1, f = tf - 1; r <= 7 && f >= 0; r++, f--)
	{
		attacks |= (1ULL << (r * 8 + f));
		if ((1ULL << (r * 8 + f)) & block.getBoard()) break;
	}

	for (r = tr - 1, f = tf - 1; r >= 0 && f >= 0; r--, f--)
	{
		attacks |= (1ULL << (r * 8 + f));
		if ((1ULL << (r * 8 + f)) & block.getBoard()) break;
	}

	// return attack map
	return attacks;
}

Bitboard ChessState::getRookAttacksSlow(int square, Bitboard block)
{
	// result attacks bitboard
	U64 attacks = 0ULL;

	// init ranks & files
	int r, f;

	// init target rank & files
	int tr = square / 8;
	int tf = square % 8;

	// generate rook attacks
	for (r = tr + 1; r <= 7; r++)
	{
		attacks |= (1ULL << (r * 8 + tf));
		if ((1ULL << (r * 8 + tf)) & block.getBoard()) break;
	}

	for (r = tr - 1; r >= 0; r--)
	{
		attacks |= (1ULL << (r * 8 + tf));
		if ((1ULL << (r * 8 + tf)) & block.getBoard()) break;
	}

	for (f = tf + 1; f <= 7; f++)
	{
		attacks |= (1ULL << (tr * 8 + f));
		if ((1ULL << (tr * 8 + f)) & block.getBoard()) break;
	}

	for (f = tf - 1; f >= 0; f--)
	{
		attacks |= (1ULL << (tr * 8 + f));
		if ((1ULL << (tr * 8 + f)) & block.getBoard()) break;
	}

	// return attack map
	return attacks;
}

Bitboard ChessState::getBishopAttacks(int square, U64 occupancy)
{
	// get bishop attacks assuming current board occupancy
	occupancy &= s_BISHOP_MASKS[square].getBoard();
	occupancy *= c_BISHOP_MAGICS[square];
	occupancy >>= 64 - c_BISHOP_INDEX_BITS[square];

	// return bishop attacks
	return s_BISHOP_ATTACKS[square][occupancy];
}

Bitboard ChessState::getRookAttacks(int square, U64 occupancy)
{
	// get bishop attacks assuming current board occupancy
	occupancy &= s_ROOK_MASKS[square].getBoard();
	occupancy *= c_ROOK_MAGICS[square];
	occupancy >>= 64 - c_ROOK_INDEX_BITS[square];

	// return bishop attacks
	return s_ROOK_ATTACKS[square][occupancy];
}

Bitboard ChessState::getQueenAttacks(int square, U64 occupancy)
{
	return this->getBishopAttacks(square, occupancy).getBoard() | this->getRookAttacks(square, occupancy).getBoard();
}

Bitboard ChessState::getNonSlidingPieceAttacks(Pieces piece, int square)
{
	return nonSlidingAttacks[piece][square];
}

std::vector<ChessMove> ChessState::generateLegalMoves()
{
	std::vector<ChessMove> allMoves = this->generateAllMoves();
	std::vector<ChessMove> legalMoves = std::vector<ChessMove>();

	for (ChessMove move : allMoves) {
		if (this->makeMove(move))
			legalMoves.push_back(move);
	}

	return legalMoves;
}

std::unique_ptr<ChessState> ChessState::getNextState(ChessMove m)
{
	return this->makeMove(m);
}

Bitboard ChessState::generateBishopAttackMask(int square)
{
	// result attacks bitboard
	U64 attacks = 0ULL;

	// init ranks & files
	int r, f;

	// init target rank & files
	int tr = square / 8;
	int tf = square % 8;

	// mask relevant bishop occupancy bits
	for (r = tr + 1, f = tf + 1; r <= 6 && f <= 6; r++, f++)
		attacks |= (1ULL << (r * 8 + f));
	for (r = tr - 1, f = tf + 1; r >= 1 && f <= 6; r--, f++) attacks |= (1ULL << (r * 8 + f));
	for (r = tr + 1, f = tf - 1; r <= 6 && f >= 1; r++, f--) attacks |= (1ULL << (r * 8 + f));
	for (r = tr - 1, f = tf - 1; r >= 1 && f >= 1; r--, f--) attacks |= (1ULL << (r * 8 + f));

	// return attack map
	return attacks;
}

Bitboard ChessState::generateRookAttackMask(int square)
{
	// result attacks bitboard
	U64 attacks = 0ULL;

	// init ranks & files
	int r, f;

	// init target rank & files
	int tr = square / 8;
	int tf = square % 8;

	// mask relevant rook occupancy bits
	for (r = tr + 1; r <= 6; r++) attacks |= (1ULL << (r * 8 + tf));
	for (r = tr - 1; r >= 1; r--) attacks |= (1ULL << (r * 8 + tf));
	for (f = tf + 1; f <= 6; f++) attacks |= (1ULL << (tr * 8 + f));
	for (f = tf - 1; f >= 1; f--) attacks |= (1ULL << (tr * 8 + f));

	// return attack map
	return attacks;
}

void ChessState::generateOccupancyBoards()
{
	for (int i = 0; i < 3; i++)
		this->occupancies_[i] = 0ULL;

	for (int i = Pieces::P; i <= Pieces::K; i++)
		this->occupancies_[Color::White] |= this->bitboards[i].getBoard();

	for (int i = Pieces::p; i <= Pieces::k; i++)
		this->occupancies_[Color::Black] |= this->bitboards[i].getBoard();

	this->occupancies_[Color::Both] |= this->occupancies_[Color::White];
	this->occupancies_[Color::Both] |= this->occupancies_[Color::Black];
}

Bitboard ChessState::setOccupancy(int index, int bitsInMask, Bitboard attackMask)
{
	U64 blockers = 0ULL;
	for (int i = 0; i < bitsInMask; i++) {
		int bitPos = attackMask.popLsb();
		if (index & (1 << i)) {
			blockers |= (1ULL << bitPos);
		}
	}
	return blockers;
}

std::unique_ptr<ChessState> ChessState::makeMove(ChessMove m)
{
	std::unique_ptr<ChessState> nextState = std::unique_ptr<ChessState>(new ChessState(*this));

	// Parse move
	int sourceSquare = m.source();
	int targetSquare = m.target();
	int piece = m.piece();
	int promotedPiece = m.promotion();
	int capture = m.capture();
	int doublePush = m.doublePush();
	int enpassant = m.enpassant();
	int castling = m.castling();

	// Move the piece
	nextState->bitboards[piece].disableBit(sourceSquare);
	nextState->bitboards[piece].setBit(targetSquare);

	if (capture) {
		int startPiece, endPiece;

		// white getting captured
		if (this->side_ == Color::Black) {
			startPiece = Pieces::P;
			endPiece = Pieces::K;
		}
		// black getting captured
		else {
			startPiece = Pieces::p;
			endPiece = Pieces::k;
		}

		for (int bitboardPiece = startPiece; bitboardPiece <= endPiece; bitboardPiece++) {
			if (nextState->bitboards[bitboardPiece].getBit(targetSquare)) {
				nextState->bitboards[bitboardPiece].disableBit(targetSquare);
				break;
			}
		}
	}

	// Handle promotions
	if (promotedPiece) {
		// Remove white pawn
		if (this->side_ == Color::White)
			nextState->bitboards[Pieces::P].disableBit(targetSquare);
		// Remove black pawn
		else
			nextState->bitboards[Pieces::p].disableBit(targetSquare);

		// Promote
		nextState->bitboards[promotedPiece].setBit(targetSquare);
	}

	if (enpassant) {
		// Remove captured black pawn
		if (this->side_ == Color::White)
			nextState->bitboards[Pieces::p].disableBit(targetSquare + 8);
		// Remove captured white pawn
		else
			nextState->bitboards[Pieces::P].disableBit(targetSquare - 8);
	}

	nextState->enpassant_ = 0ULL;

	if (doublePush) {
		if (this->side_ == Color::White)
			nextState->enpassant_ = targetSquare + 8;
		else
			nextState->enpassant_ = targetSquare - 8;
	}

	// Handle castling
	if (castling) {
		switch (targetSquare) {
		case Positions::g1:
			nextState->bitboards[Pieces::R].disableBit(Positions::h1);
			nextState->bitboards[Pieces::R].setBit(Positions::f1);
			break;
		case Positions::g8:
			nextState->bitboards[Pieces::r].disableBit(Positions::h8);
			nextState->bitboards[Pieces::r].setBit(Positions::f8);
			break;
		case Positions::c1:
			nextState->bitboards[Pieces::R].disableBit(Positions::a1);
			nextState->bitboards[Pieces::R].setBit(Positions::d1);
			break;
		case Positions::c8:
			nextState->bitboards[Pieces::r].disableBit(Positions::a8);
			nextState->bitboards[Pieces::r].setBit(Positions::d8);
			break;
		}
	}

	// Update castling rules
	nextState->castle_ &= c_CASTLING_RIGHTS[sourceSquare];
	nextState->castle_ &= c_CASTLING_RIGHTS[targetSquare];

	// Re-generate occupancies
	nextState->generateOccupancyBoards();

	// Switch sides
	nextState->side_ = (nextState->side_ == Color::White ? Color::Black : Color::White);

	// if illegal, return nullptr
	if (nextState->isSquareAttacked((this->side_ == Color::White ? nextState->bitboards[Pieces::K].getLsb() : nextState->bitboards[Pieces::k].getLsb()), nextState->side_)) {
		return nullptr;
	}

	return nextState;
}

std::vector<ChessMove> ChessState::generateAllMoves()
{
	std::vector<ChessMove> allMoves = std::vector<ChessMove>();

	int source_square, target_square;
	Bitboard bitboard, attacks;
	Bitboard occupanciesBoth = Bitboard(this->occupancies_[Color::Both]);
	Bitboard occupanciesBlack = Bitboard(this->occupancies_[Color::Black]);
	Bitboard occupanciesWhite = Bitboard(this->occupancies_[Color::White]);

	for (int piece = 0; piece < this->c_PIECES_AMOUNT; piece++) {
		bitboard = this->bitboards[piece];

		// We need to do special king castling rules and pawn movement for the specific side
		if (this->side_ == Color::White) {
			// pick up white pawn bitboards index
			if (piece == Pieces::P)
			{
				// loop over white pawns within white pawn bitboard
				while (bitboard.getBoard())
				{
					// init source square
					source_square = bitboard.popLsb();

					// init target square
					target_square = source_square - 8;

					// generate quiet pawn moves
					if (!(target_square < Positions::a8) && !occupanciesBoth.getBit(target_square))
					{
						// pawn promotion
						if (source_square >= Positions::a7 && source_square <= Positions::h7)
						{
							allMoves.push_back(ChessMove(source_square, target_square, piece, Pieces::Q, 0, 0, 0, 0));
							allMoves.push_back(ChessMove(source_square, target_square, piece, Pieces::R, 0, 0, 0, 0));
							allMoves.push_back(ChessMove(source_square, target_square, piece, Pieces::B, 0, 0, 0, 0));
							allMoves.push_back(ChessMove(source_square, target_square, piece, Pieces::N, 0, 0, 0, 0));
						}

						else
						{
							// one square ahead pawn move
							allMoves.push_back(ChessMove(source_square, target_square, piece, 0, 0, 0, 0, 0));

							// two squares ahead pawn move
							if ((source_square >= a2 && source_square <= h2) && !occupanciesBoth.getBit(target_square - 8))
								allMoves.push_back(ChessMove(source_square, target_square - 8, piece, 0, 0, 1, 0, 0));
						}
					}

					// init pawn attacks bitboard
					attacks = Bitboard(nonSlidingAttacks[Pieces::P][source_square] & occupanciesBlack.getBoard());

					// generate pawn captures
					while (attacks.getBoard())
					{
						// init target square
						target_square = attacks.popLsb();

						// pawn promotion
						if (source_square >= Positions::a7 && source_square <= Positions::h7)
						{
							allMoves.push_back(ChessMove(source_square, target_square, piece, Pieces::Q, 1, 0, 0, 0));
							allMoves.push_back(ChessMove(source_square, target_square, piece, Pieces::R, 1, 0, 0, 0));
							allMoves.push_back(ChessMove(source_square, target_square, piece, Pieces::B, 1, 0, 0, 0));
							allMoves.push_back(ChessMove(source_square, target_square, piece, Pieces::N, 1, 0, 0, 0));
						}

						else
							// one square ahead pawn move
							allMoves.push_back(ChessMove(source_square, target_square, piece, 0, 1, 0, 0, 0));
					}

					// generate enpassant captures
					if (this->enpassant_ != 0ULL)
					{
						// lookup pawn attacks and bitwise AND with enpassant square (bit)
						U64 enpassant_attacks = nonSlidingAttacks[Pieces::P][source_square] & (1ULL << this->enpassant_);

						// make sure enpassant capture available
						if (enpassant_attacks)
						{
							// init enpassant capture target square
							int target_enpassant = Bitboard(enpassant_attacks).popLsb();
							allMoves.push_back(ChessMove(source_square, target_enpassant, piece, 0, 1, 0, 1, 0));
						}
					}
				}
			}

			// castling moves
			if (piece == K)
			{
				// king side castling is available
				if (this->castle_ & Castling::wk)
				{
					// make sure square between king and king's rook are empty
					if (!occupanciesBoth.getBit(Positions::f1) && !occupanciesBoth.getBit(g1))
					{
						// make sure king and the f1 squares are not under attacks
						if (!this->isSquareAttacked(Positions::e1, Color::Black) && !this->isSquareAttacked(Positions::f1, Color::Black))
							allMoves.push_back(ChessMove(e1, g1, piece, 0, 0, 0, 0, 1));
					}
				}

				// queen side castling is available
				if (this->castle_ & Castling::wq)
				{
					// make sure square between king and queen's rook are empty
					if (!occupanciesBoth.getBit(Positions::d1) && !occupanciesBoth.getBit(Positions::c1) && !occupanciesBoth.getBit(Positions::b1))
					{
						// make sure king and the d1 squares are not under attacks
						if (!this->isSquareAttacked(Positions::e1, Color::Black) && !this->isSquareAttacked(Positions::d1, Color::Black))
							allMoves.push_back(ChessMove(e1, c1, piece, 0, 0, 0, 0, 1));
					}
				}
			}
		}
		else {
			// pick up black pawn bitboards index
			if (piece == Pieces::p)
			{
				// loop over white pawns within white pawn bitboard
				while (bitboard.getBoard())
				{
					// init source square
					source_square = bitboard.popLsb();

					// init target square
					target_square = source_square + 8;

					// generate quiet pawn moves
					if (!(target_square > Positions::h1) && !occupanciesBoth.getBit(target_square))
					{
						// pawn promotion
						if (source_square >= Positions::a2 && source_square <= Positions::h2)
						{
							allMoves.push_back(ChessMove(source_square, target_square, piece, Pieces::q, 0, 0, 0, 0));
							allMoves.push_back(ChessMove(source_square, target_square, piece, Pieces::r, 0, 0, 0, 0));
							allMoves.push_back(ChessMove(source_square, target_square, piece, Pieces::b, 0, 0, 0, 0));
							allMoves.push_back(ChessMove(source_square, target_square, piece, Pieces::n, 0, 0, 0, 0));
						}

						else
						{
							// one square ahead pawn move
							allMoves.push_back(ChessMove(source_square, target_square, piece, 0, 0, 0, 0, 0));

							// two squares ahead pawn move
							if ((source_square >= Positions::a7 && source_square <= Positions::h7) && !occupanciesBoth.getBit(target_square + 8))
								allMoves.push_back(ChessMove(source_square, target_square + 8, piece, 0, 0, 1, 0, 0));
						}
					}

					// init pawn attacks bitboard
					attacks = Bitboard(nonSlidingAttacks[Pieces::p][source_square] & occupanciesWhite.getBoard());

					// generate pawn captures
					while (attacks.getBoard())
					{
						// init target square
						target_square = attacks.popLsb();

						// pawn promotion
						if (source_square >= Positions::a2 && source_square <= Positions::h2)
						{
							allMoves.push_back(ChessMove(source_square, target_square, piece, q, 1, 0, 0, 0));
							allMoves.push_back(ChessMove(source_square, target_square, piece, r, 1, 0, 0, 0));
							allMoves.push_back(ChessMove(source_square, target_square, piece, b, 1, 0, 0, 0));
							allMoves.push_back(ChessMove(source_square, target_square, piece, n, 1, 0, 0, 0));
						}

						else
							// one square ahead pawn move
							allMoves.push_back(ChessMove(source_square, target_square, piece, 0, 1, 0, 0, 0));
					}

					// generate enpassant captures
					if (this->enpassant_ != 0ULL)
					{
						// lookup pawn attacks and bitwise AND with enpassant square (bit)
						U64 enpassant_attacks = nonSlidingAttacks[(this->side_ == Color::White ? Pieces::P : Pieces::p)][source_square] & (1ULL << this->enpassant_);

						// make sure enpassant capture available
						if (enpassant_attacks)
						{
							// init enpassant capture target square
							int target_enpassant = Bitboard(enpassant_attacks).popLsb();
							allMoves.push_back(ChessMove(source_square, target_enpassant, piece, 0, 1, 0, 1, 0));
						}
					}
				}
			}

			// castling moves
			if (piece == k)
			{
				// king side castling is available
				if (this->castle_ & Castling::bk)
				{
					// make sure square between king and king's rook are empty
					if (!occupanciesBoth.getBit(Positions::f8) && !occupanciesBoth.getBit(Positions::g8))
					{
						// make sure king and the f8 squares are not under attacks
						if (!this->isSquareAttacked(Positions::e8, Color::White) && !this->isSquareAttacked(Positions::f8, Color::White))
							allMoves.push_back(ChessMove(e8, g8, piece, 0, 0, 0, 0, 1));
					}
				}

				// queen side castling is available
				if (this->castle_ & Castling::bq)
				{
					// make sure square between king and queen's rook are empty
					if (!occupanciesBoth.getBit(Positions::d8) && !occupanciesBoth.getBit(Positions::c8) && !occupanciesBoth.getBit(Positions::b8))
					{
						// make sure king and the d8 squares are not under attacks
						if (!this->isSquareAttacked(Positions::e8, Color::White) && !this->isSquareAttacked(Positions::d8, Color::White))
							allMoves.push_back(ChessMove(e8, c8, piece, 0, 0, 0, 0, 1));
					}
				}
			}
		}

		// genarate knight moves
		if ((this->side_ == Color::White) ? piece == Pieces::N : piece == Pieces::n)
		{
			// loop over source squares of piece bitboard copy
			while (bitboard.getBoard())
			{
				// init source square
				source_square = bitboard.popLsb();

				// init piece attacks in order to get set of target squares
				attacks = Bitboard(nonSlidingAttacks[piece][source_square] & ((this->side_ == Color::White) ? ~occupanciesWhite.getBoard() : ~occupanciesBlack.getBoard()));

				// loop over target squares available from generated attacks
				while (attacks.getBoard())
				{
					// init target square
					target_square = attacks.popLsb();

					// quiet move
					if (!((this->side_ == Color::White) ? occupanciesBlack : occupanciesWhite).getBit(target_square))
						allMoves.push_back(ChessMove(source_square, target_square, piece, 0, 0, 0, 0, 0));
					else
						// capture move
						allMoves.push_back(ChessMove(source_square, target_square, piece, 0, 1, 0, 0, 0));
				}
			}
		}

		// generate bishop moves
		if ((this->side_ == Color::White) ? piece == B : piece == b)
		{
			// loop over source squares of piece bitboard copy
			while (bitboard.getBoard())
			{
				// init source square
				source_square = bitboard.popLsb();

				// init piece attacks in order to get set of target squares
				attacks = Bitboard(this->getBishopAttacks(source_square, occupanciesBoth.getBoard()).getBoard() & ((this->side_ == Color::White) ? ~occupanciesWhite.getBoard() : ~occupanciesBlack.getBoard()));

				// loop over target squares available from generated attacks
				while (attacks.getBoard())
				{
					// init target square
					target_square = attacks.popLsb();

					// quiet move
					if (!((this->side_ == Color::White) ? occupanciesBlack : occupanciesWhite).getBit(target_square))
						allMoves.push_back(ChessMove(source_square, target_square, piece, 0, 0, 0, 0, 0));
					else
						// capture move
						allMoves.push_back(ChessMove(source_square, target_square, piece, 0, 1, 0, 0, 0));
				}
			}
		}

		// generate rook moves
		if ((this->side_ == Color::White) ? piece == R : piece == r)
		{
			// loop over source squares of piece bitboard copy
			while (bitboard.getBoard())
			{
				// init source square
				source_square = bitboard.popLsb();

				// init piece attacks in order to get set of target squares
				attacks = Bitboard(this->getRookAttacks(source_square, occupanciesBoth.getBoard()).getBoard() & ((this->side_ == Color::White) ? ~occupanciesWhite.getBoard() : ~occupanciesBlack.getBoard()));

				// loop over target squares available from generated attacks
				while (attacks.getBoard())
				{
					// init target square
					target_square = attacks.popLsb();

					// quiet move
					if (!((this->side_ == Color::White) ? occupanciesBlack : occupanciesWhite).getBit(target_square))
						allMoves.push_back(ChessMove(source_square, target_square, piece, 0, 0, 0, 0, 0));

					else
						// capture move
						allMoves.push_back(ChessMove(source_square, target_square, piece, 0, 1, 0, 0, 0));
				}
			}
		}

		// generate queen moves
		if ((this->side_ == Color::White) ? piece == Pieces::Q : piece == Pieces::q)
		{
			// loop over source squares of piece bitboard copy
			while (bitboard.getBoard())
			{
				// init source square
				source_square = bitboard.popLsb();

				// init piece attacks in order to get set of target squares
				attacks = Bitboard(this->getQueenAttacks(source_square, occupanciesBoth.getBoard()).getBoard() & ((this->side_ == Color::White) ? ~occupanciesWhite.getBoard() : ~occupanciesBlack.getBoard()));

				// loop over target squares available from generated attacks
				while (attacks.getBoard())
				{
					// init target square
					target_square = attacks.popLsb();

					// quiet move
					if (!((this->side_ == Color::White) ? occupanciesBlack : occupanciesWhite).getBit(target_square))
						allMoves.push_back(ChessMove(source_square, target_square, piece, 0, 0, 0, 0, 0));

					else
						// capture move
						allMoves.push_back(ChessMove(source_square, target_square, piece, 0, 1, 0, 0, 0));
				}
			}
		}

		// generate king moves
		if ((this->side_ == Color::White) ? piece == K : piece == k)
		{
			// loop over source squares of piece bitboard copy
			while (bitboard.getBoard())
			{
				// init source square
				source_square = bitboard.popLsb();

				// init piece attacks in order to get set of target squares
				attacks = Bitboard(nonSlidingAttacks[piece][source_square] & ((this->side_ == Color::White) ? ~occupanciesWhite.getBoard() : ~occupanciesBlack.getBoard()));

				// loop over target squares available from generated attacks
				while (attacks.getBoard())
				{
					// init target square
					target_square = attacks.popLsb();

					// quiet move
					if (!((this->side_ == Color::White) ? occupanciesBlack : occupanciesWhite).getBit(target_square))
						allMoves.push_back(ChessMove(source_square, target_square, piece, 0, 0, 0, 0, 0));

					else
						// capture move
						allMoves.push_back(ChessMove(source_square, target_square, piece, 0, 1, 0, 0, 0));
				}
			}
		}
	}

	return allMoves;
}
