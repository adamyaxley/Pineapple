template <std::size_t N>
void pa::TileMap::setFromArray(pa::Tile(&tiles)[N])
{
	PA_ASSERTF(getSizeConst().x * getSizeConst().y == N, "Passed array is not the correct size");
	for (int y = 0; y < getSizeConst().y; y++)
	{
		for (int x = 0; x < getSizeConst().x; x++)
		{
			set(x, y, tiles[y * getSizeConst().x + x]);
		}
	}
}
