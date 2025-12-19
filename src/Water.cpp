#include "PCH.hpp"

#include "Water.hpp"

void Water::load()
{
    unload();

    // Load terrain data from image.
    Ogre::Image image;
    image.load("water.png", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

    /// Create the mesh via the MeshManager
    Ogre::MeshPtr msh = Ogre::MeshManager::getSingleton().createManual(name, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
 
    /// Create one submesh
    Ogre::SubMesh* sub = msh->createSubMesh();
 
    /// Define the vertices (8 vertices, each consisting of 2 groups of 3 floats
    size_t nVertices = image.getWidth() * image.getHeight();
    size_t vbufCount = nVertices * 3;

    float* vertices = new float[vbufCount];
    Ogre::RGBA* colours = new Ogre::RGBA[nVertices];
    Ogre::RGBA *pColour = colours;
    water = new float[nVertices];

    Ogre::RenderSystem* rs = Ogre::Root::getSingleton().getRenderSystem();

    for (size_t z = 0; z < image.getHeight(); ++z)
    {
        for (size_t x = 0; x < image.getWidth(); ++x)
        {
            Ogre::uchar y = image.getData()[z * image.getWidth() + x];

            //water[(z * image.getWidth() + x) * 3    ] = x * 10.0f;
            //water[(z * image.getWidth() + x) * 3 + 1] = y * 1.0f;
            //water[(z * image.getWidth() + x) * 3 + 2] = z * 10.0f;

            water[z * image.getWidth() + x] = y * 1.0f;

            vertices[(z * image.getWidth() + x) * 3    ] = x * 10.0f;
            vertices[(z * image.getWidth() + x) * 3 + 1] = (terrain->getHeight(x, z) + y) * 1.0f;
            vertices[(z * image.getWidth() + x) * 3 + 2] = z * 10.0f;

            Ogre::ColourValue colour(
                0.0f,
                1.0f - (y - terrain->getHeight(x, z)) / 255.0f,
                1.0f,
                0.3f);

            rs->convertColourValue(colour, pColour++);
        }
    }

    /// Define 12 triangles (two triangles per cube face)
    /// The values in this table refer to vertices in the above table
    const size_t ibufCount = (image.getHeight() - 1) * (image.getWidth() - 1) * 6;
    Ogre::uint16* faces = new Ogre::uint16[ibufCount];
    
    for (size_t z = 0; z < image.getHeight() - 1; ++z)
    {
        for (size_t x = 0; x < image.getWidth() - 1; ++x)
        {
            faces[(z * (image.getWidth() - 1) + x) * 6    ] = z * image.getWidth() + x;
            faces[(z * (image.getWidth() - 1) + x) * 6 + 1] = (z + 1) * image.getWidth() + x;
            faces[(z * (image.getWidth() - 1) + x) * 6 + 2] = z * image.getWidth() + x + 1;

            faces[(z * (image.getWidth() - 1) + x) * 6 + 3] = z * image.getWidth() + x + 1;
            faces[(z * (image.getWidth() - 1) + x) * 6 + 4] = (z + 1) * image.getWidth() + x;
            faces[(z * (image.getWidth() - 1) + x) * 6 + 5] = (z + 1) * image.getWidth() + x + 1;
        }
    }
 
    /// Create vertex data structure for 8 vertices shared between submeshes
    msh->sharedVertexData = new Ogre::VertexData();
    msh->sharedVertexData->vertexCount = nVertices;
 
    /// Create declaration (memory format) of vertex data
    Ogre::VertexDeclaration* decl = msh->sharedVertexData->vertexDeclaration;
    size_t offset = 0;
    // 1st buffer
    decl->addElement(0, offset, Ogre::VET_FLOAT3, Ogre::VES_POSITION);
    offset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT3);

    //decl->addElement(0, offset, Ogre::VET_FLOAT3, Ogre::VES_NORMAL);
    //offset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT3);

    /// Allocate vertex buffer of the requested number of vertices (vertexCount) 
    /// and bytes per vertex (offset)
    Ogre::HardwareVertexBufferSharedPtr vbuf = 
        Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(
        offset, msh->sharedVertexData->vertexCount, Ogre::HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY_DISCARDABLE);
    /// Upload the vertex data to the card
    vbuf->writeData(0, vbuf->getSizeInBytes(), vertices, true);
 
    /// Set vertex buffer binding so buffer 0 is bound to our vertex buffer
    Ogre::VertexBufferBinding* bind = msh->sharedVertexData->vertexBufferBinding; 
    bind->setBinding(0, vbuf);
 
    // 2nd buffer
    offset = 0;
    decl->addElement(1, offset, Ogre::VET_COLOUR, Ogre::VES_DIFFUSE);
    offset += Ogre::VertexElement::getTypeSize(Ogre::VET_COLOUR);
    /// Allocate vertex buffer of the requested number of vertices (vertexCount) 
    /// and bytes per vertex (offset)
    vbuf = Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(
        offset, msh->sharedVertexData->vertexCount, Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY);
    /// Upload the vertex data to the card
    vbuf->writeData(0, vbuf->getSizeInBytes(), colours, true);
 
    /// Set vertex buffer binding so buffer 1 is bound to our colour buffer
    bind->setBinding(1, vbuf);
 
    /// Allocate index buffer of the requested number of vertices (ibufCount) 
    Ogre::HardwareIndexBufferSharedPtr ibuf = Ogre::HardwareBufferManager::getSingleton().
        createIndexBuffer(
        Ogre::HardwareIndexBuffer::IT_16BIT, 
        ibufCount, 
        Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY);
 
    /// Upload the index data to the card
    ibuf->writeData(0, ibuf->getSizeInBytes(), faces, true);
 
    /// Set parameters of the submesh
    sub->useSharedVertices = true;
    sub->indexData->indexBuffer = ibuf;
    sub->indexData->indexCount = ibufCount;
    sub->indexData->indexStart = 0;
 
    /// Set bounding information (for culling)
    msh->_setBounds(Ogre::AxisAlignedBox(0.0f, 0.0f, 0.0f, 1000.0f, 1000.0f, 1000.0f));
    msh->_setBoundingSphereRadius(Ogre::Math::Sqrt(1000.0f));
 
    /// Notify -Mesh object that it has been loaded
    msh->load();

    // Create entity.
    entity = scene->createEntity(name, name);
    entity->setMaterialName("Water");
    entity->setUserAny(Ogre::Any(this));

    // Create scene node.
    sceneNode = scene->createSceneNode(name);
    sceneNode->attachObject(entity);
    sceneNode->setUserAny(Ogre::Any(this));
}

void Water::unload()
{
    if (entity)
    {
        scene->destroyEntity(entity);
    }
    
    if (sceneNode)
    {
        scene->destroySceneNode(sceneNode);
    }

    entity = NULL;
    sceneNode = NULL;
}

//
// http://wscg.zcu.cz/wscg2002/Papers_2002/F23.pdf
//
void Water::update(float time)
{ 
	const size_t width = 129;
	const size_t height = 129;

    float* tempWater = new float[width * height];

    for (int i = 0; i < width * height; ++i)
    {
        tempWater[i] = water[i];
    }

    //const Ogre::uint16* pHeight = mHeightmap;
	const float* pSrcWater = tempWater;
	float* pDestWater = water;

	// These are for bounds checking
	const float* pSrcWaterBegin = pSrcWater;
	const float* pSrcWaterEnd = pSrcWaterBegin + width * height;

	// Offsets to neighbours
	/*
    const int offset[8][2] =
    {
        // z,  x
        { -1, -1 },
        { -1,  0 },
        { -1, +1 },
        {  0, -1 },
        {  0, +1 },
        { +1, -1 },
        { +1,  0 },
        { +1, +1 }
    };
    */

    const int offset[8] = {-(int)width-1, -(int)width, -(int)width+1,
									-1,						  +1,
						(int)width-1,  (int)width,  (int)width+1};

    for (int z = 0; z < height; ++z)
	{
		for (int x = 0; x < width; ++x)
		{
            if (*pSrcWater)
			{
                const float h = terrain->getHeight(x, z) + *pSrcWater;
				float dh[8];		// dh = h - ('height of neighbour')

				float sum = 0;	// Sum of dh[x] for all lower neighbours
				int n = 0;		// Number of lower neighbours

				// Find differences in height
				for (size_t k = 0; k < 8; k++)
				{
					const float* pNeighbourWater = pSrcWater + offset[k];

					if (pNeighbourWater >= pSrcWaterBegin && pNeighbourWater < pSrcWaterEnd)
					{
						//dh[k] = h - (*(pHeight + offset[k]) + *pNeighbourWater);
                        dh[k] = h - (terrain->getHeight(x, z, offset[k]) + *pNeighbourWater);

						if (dh[k] > 0)
						{
							sum += dh[k];
							n++;
						}
					}
					else
					{
						dh[k] = 0;
					}
				}

				// Determine the amount of water to be moved to lower neighbours
				//int dw = std::min<int>(*pSrcWater, sum) >> 3;		// stable but seems slow
				float dw = std::min<float>(*pSrcWater, sum) / (n + 1);	// seems faster but less stable

				if (dw > 0.001f)
				{
					//int transported = 0;

					// Move water to lower neighbours
					for (size_t k = 0; k < 8; k++)
					{
						if (dh[k] > 0)
						{
							float amount = (dw * dh[k]) / sum;
							*(pDestWater + offset[k]) += amount;
							//transported += amount;
						}
					}

					*pDestWater -= dw;
					//totalError += (dw - transported);
				}

				// TODO: All water is never removed.
				// Note that the texture hides everything below the value 9, so this is not visible.
			}

			//pHeight++;
			pSrcWater++;
			pDestWater++;
		}
	}


    Ogre::MeshPtr mesh = entity->getMesh();
    Ogre::SubMesh* subMesh = mesh->getSubMesh(0);

    Ogre::VertexData* vertex_data;
    vertex_data = subMesh->useSharedVertices ? mesh->sharedVertexData : subMesh->vertexData;

    const Ogre::VertexElement* posElem =
        vertex_data->vertexDeclaration->findElementBySemantic(Ogre::VES_POSITION);
 
    Ogre::HardwareVertexBufferSharedPtr vbuf =
        vertex_data->vertexBufferBinding->getBuffer(posElem->getSource());
 
    unsigned char* vertex =
        static_cast<unsigned char*>(vbuf->lock(Ogre::HardwareBuffer::HBL_DISCARD));

    for (int z = 0; z < height; ++z)
	{
		for (int x = 0; x < width; ++x)
		{
            float* pReal;
            posElem->baseVertexPointerToElement(vertex + (z * width + x) * vbuf->getVertexSize(), &pReal);

            pReal[1] = terrain->getHeight(x, z) + water[z * width + x];
        }
    }

    vbuf->unlock();
}

float Water::getHeight(size_t x, size_t z) const
{
    static bool loaded = false;
    static Ogre::Image image;

    if (loaded == false)
    {
        image.load("water.png", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

        loaded = true;
    }

    return image.getData()[z * image.getWidth() + x] * 1.0f;
}
