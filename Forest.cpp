#include "Forest.h"

Forest::Forest(Game& game, int size, float fireChance, float treeChance) 
	: GameComponent(game), size(size), fireChance(fireChance), treeChance(treeChance), currentCells(0)
{
	// zellen initialisieren
	for (int i = 0; i < 2; ++i)
		cells[i] = std::vector<byte>(size * size, 0);
}


void Forest::update(float elapsed)
{
	static float time = 0;

	time += elapsed;

	while (time > 1.0f / SPEED)
	{
		// für alle zellen
		for (int row = 0; row < size; ++row)
			for (int col = 0; col < size; ++col)
			{
				// aktuellen wert ermitteln
				int cell = get(row, col);

				// zustandsänderung je nach wert
				switch (cell)
				{
					case EMPTY: if (rand() < treeChance) cell = TREE; break;
					case TREE: if (neighborFire(row, col) || rand() < fireChance) cell = FIRE; break;
					case FIRE: cell = EMPTY; break;
				}

				// neuen wert setzen
				set(row, col, cell);
			}

		currentCells = (currentCells + 1) % 2;

		time -= 1.0f / SPEED;
	}
}


bool Forest::neighborFire(int row, int col) const
{
	// überprüfen, ob einer der nachbarn brennt
	for (int r = -1; r < 2; ++r)
		for (int c = -1; c < 2; ++c)
			if (get(row + r, col + c) == FIRE)
				return true;

	return false;
}


void Forest::draw(float elapsed)
{
	CL_Vec2<float> fieldSize;

	CL_Rect viewport = window.get_viewport();
	
	fieldSize.x = (float)viewport.get_width() / size;
	fieldSize.y = (float)viewport.get_height() / size;

	// farben für leer, baum und feuer
	CL_Colorf colors[] = { CL_Colorf::black, CL_Colorf::green, CL_Colorf::red };

	// für alle zellen
	for (int row = 0; row < size; row++)
		for (int col = 0; col < size; col++)
		{
			// farbe ermitteln und rechteck zeichnen
			CL_Colorf color = colors[get(row, col)];
			CL_Pointf p = CL_Pointf(col * fieldSize.x, row * fieldSize.y);
			CL_Draw::fill(window.get_gc(), p, p + fieldSize, color);
		}
}


void Forest::set(int row, int col, int value)
{
	int index = getIndex(row, col);
	int offset = getOffset(row, col);
	int current = (currentCells + 1) % 2;

	// wenn row und col innerhalb des feldes
	if (isValid(row, col))
	{
		// clear bits
		cells[current][index] &= ~(MASK << offset);

		// set bits
		cells[current][index] |= value << offset;
	}
}


int Forest::get(int row, int col) const
{
	// wert der zelle ermitteln
	if (isValid(row, col))
		return (cells[currentCells][getIndex(row, col)] >> getOffset(row, col)) & MASK;

	return EMPTY;
}


// liefert den index im byte array
int Forest::getIndex(int row, int col) const
{
	return (row * size + col) / 4;
}


// liefert das offset (um wieviele bits geshiftet werden muss)
int Forest::getOffset(int row, int col) const
{
	return ((row * size + col) % 4) * 2;
}


// überprüft, ob row und col innerhalb des feldes liegen
bool Forest::isValid(int row, int col) const
{
	return row >= 0 && row < size && col >= 0 && col < size;
}


// liefert einen wert zwischen 0 und 1
float Forest::rand() const
{
	return std::rand() / (RAND_MAX + 1.0f);
}