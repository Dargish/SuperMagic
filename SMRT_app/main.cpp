#include <SMRT/SMRT.h>
#include <SMRT/Scene.h>
#include <SMRT/Colliders/Sphere.h>

#include <OpenEXR/ImfRgbaFile.h>

#include <vector>
#include <iostream>

SMRT_NAMESPACE_USING;

typedef std::vector<RGBA> RenderBuffer;
typedef std::vector<Imf::Rgba> OpenEXRBuffer;

void fillTestBuffer(size_t res_x, size_t res_y, RenderBuffer& renderBuffer)
{
	float delta_x = 1.0f / res_x;
	float delta_y = 1.0f / res_y;
	for (size_t x = 0; x < res_x; ++x)
	{
		for (size_t y = 0; y < res_y; ++y)
		{
			size_t index = y * res_x + x;
			renderBuffer[index].r = x * delta_x;
			renderBuffer[index].b = y * delta_y;
		}
	}
}

void translateBuffer(const RenderBuffer& renderBuffer, OpenEXRBuffer& outputBuffer)
{
	if (outputBuffer.size() != renderBuffer.size())
	{
		outputBuffer.resize(renderBuffer.size());
	}
	for(size_t i = 0; i < renderBuffer.size(); ++i)
	{
		outputBuffer[i].r = renderBuffer[i].r;
		outputBuffer[i].g = renderBuffer[i].g;
		outputBuffer[i].b = renderBuffer[i].b;
		outputBuffer[i].a = renderBuffer[i].a;
	}
}

int main()
{
	size_t resolution_x = 1280;
	size_t resolution_y = 720;
	size_t pixel_count = resolution_x * resolution_y;

	RenderBuffer renderBuffer(pixel_count);
//	fillTestBuffer(resolution_x, resolution_y, renderBuffer);

	Scene scene;
	SceneObject sceneObject;
	sceneObject.setCollider(new Sphere);
	scene.push_back(sceneObject);

	Ray ray;
	float distance = -1.0f;

	std::cerr << "Collider intersect: " << sceneObject.collider().intersect(ray, distance) << std::endl;

	OpenEXRBuffer outputBuffer(pixel_count);

	translateBuffer(renderBuffer, outputBuffer);

	std::string fileName = "test_image.exr";

	Imf::RgbaOutputFile outputFile(fileName.c_str(), resolution_x, resolution_y, Imf::WRITE_RGBA);
	outputFile.setFrameBuffer(&outputBuffer.front(), 1, resolution_x);
	outputFile.writePixels(resolution_y);

	return 0;
}