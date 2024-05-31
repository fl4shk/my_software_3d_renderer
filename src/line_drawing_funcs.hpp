#ifndef src_line_drawing_funcs_hpp
#define src_line_drawing_funcs_hpp
//--------
#include "misc_includes.hpp"

template<typename Type>
inline std::vector<Vec2<Type>> line_coords(const Vec2<Type>& v0,
	const Vec2<Type>& v1, const Vec2<size_t>& screen_size_2d)
{
	std::vector<Vec2<Type>> ret;

	Vec2<Type> delta, pixel_coord, offset;

	delta = {v1.x - v0.x, v1.y - v0.y};

	if (delta.x < 0)
	{
		delta.x = -delta.x;
	}
	if (delta.y < 0)
	{
		delta.y = -delta.y;
	}

	pixel_coord = v0;

	if (v0.x > v1.x)
	{
		offset.x = -1;
	}
	else
	{
		offset.x = 1;
	}

	if (v0.y > v1.y)
	{
		offset.y = -1;
	}
	else
	{
		offset.y = 1;
	}

	//m4_plot(pixel_coord.x, pixel_coord.y, color_id, page);
	auto draw_one = [&]() -> bool
	{
		if ((pixel_coord.x < 0) || (pixel_coord.x >= screen_size_2d.x)
			|| (pixel_coord.y < 0) || (pixel_coord.y >= screen_size_2d.y))
		{
			return false;
		}

		ret.push_back(pixel_coord);
		return true;
	};

	if (!draw_one(pixel_coord))
	{
		return ret;
	}

	auto draw 
		= [&]
		(
			Type& delta_0, Type& delta_1,
			Type& pixel_coord_0, Type& pixel_coord_1,
			Type& v1_0,
			Type& offset_0, Type& offset_1
		) -> decltype(ret)
	{
		Type error = delta_0 >> 1;

		while (pixel_coord_0 != v1_0)
		{
			error -= delta_1;

			if (error < 0)
			{
				pixel_coord_1 += offset_1;
				error += delta_0;
			}
			
			pixel_coord_0 += offset_0;

			//m4_plot(pixel_coord_0, pixel_coord_1, color_id, page);
			if (!draw_one())
			{
				break;
			}
		}
		return ret;
	};
	if (delta.x > delta.y)
	{
		return draw
		(
			delta.x, delta.y,
			pixel_coord.x, pixel_coord.y,
			v1.x, 
			offset.x, offset.y
		);
	}
	else // if (delta.x <= delta.y)
	{
		return draw
		(
			delta.y, delta.x,
			pixel_coord.y, pixel_coord.x,
			v1.y, 
			offset.y, offset.x
		);
	}
}
#endif		// src_line_drawing_funcs_hpp
