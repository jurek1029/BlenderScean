#ifndef VectexFormat_H_
#define VectexFormat_H_

#include "glm\glm.hpp"

namespace BasicEngine
{
	namespace Rendering
	{
		struct VertexFormatBase
		{
		};

		struct VertexFormat : VertexFormatBase
		{
			glm::vec3 position;		
			glm::vec4 color;
			glm::vec2 texture;		
			
			VertexFormat(const glm::vec3 &iPos, const glm::vec4 &iColor) :position(iPos), color(iColor) 
			{
				texture.x = texture.y = 0;
			}
			
			VertexFormat(const glm::vec3 &iPos, const glm::vec2 &iTexture): position(iPos), texture(iTexture)
			{
				color.r = color.g = color.b = color.a = 0;
			}

			VertexFormat() {}
		};

		struct VertexFormatC : VertexFormatBase
		{
			glm::vec3 position;
			glm::vec4 color;

			VertexFormatC(const glm::vec3 &iPos, const glm::vec4 &iColor) : color(iColor)
			{
				position = iPos;
			}

			VertexFormatC() {}
		};

		struct VertexFormatP : VertexFormatBase // mask 0
		{
			glm::vec3 position;

			VertexFormatP(const glm::vec3 &iPos) : position(iPos)
			{
			}

			VertexFormatP() {}
		};

		struct VertexFormatN : VertexFormatBase // mask 1
		{
			glm::vec3 position;
			glm::vec3 normal;

			VertexFormatN(const glm::vec3 &iPos, const glm::vec3 &iNorm) :position(iPos), normal(iNorm)
			{
			}

			VertexFormatN() {}
		};
		struct VertexFormatUV : VertexFormatBase // mask 2
		{
			glm::vec3 position;
			glm::vec2 texture;

			VertexFormatUV(const glm::vec3 &iPos, const glm::vec2 &iTexture) :position(iPos), texture(iTexture)
			{
			}

			VertexFormatUV() {}
		};

		struct VertexFormatNUV : VertexFormatBase // mask 3
		{
			glm::vec3 position;
			glm::vec3 normal;
			glm::vec2 texture;

			VertexFormatNUV(const glm::vec3 &iPos, const glm::vec3 &iNorm, const glm::vec2 &iTexture) :position(iPos),
				normal(iNorm),texture(iTexture) 
			{
			}

			VertexFormatNUV() {}
		};
	}
}
#endif