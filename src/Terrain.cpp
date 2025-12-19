#include "PCH.hpp"

#include "Terrain.hpp"

void Terrain::load()
{
    unload();

    /*
    // Load terrain data from image.
    Ogre::Image image;
    image.load("terrain.png", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

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

    Ogre::RenderSystem* rs = Ogre::Root::getSingleton().getRenderSystem();

    for (size_t z = 0; z < image.getHeight(); ++z)
    {
        for (size_t x = 0; x < image.getWidth(); ++x)
        {
            Ogre::uchar y = image.getData()[z * image.getWidth() + x];

            vertices[(z * image.getWidth() + x) * 3    ] = x * 10.0f;
            vertices[(z * image.getWidth() + x) * 3 + 1] = y * 1.0f;
            vertices[(z * image.getWidth() + x) * 3 + 2] = z * 10.0f;

            Ogre::ColourValue colour(
                image.getData()[z * image.getWidth() + x] / 255.0f,
                image.getData()[z * image.getWidth() + x] / 255.0f,
                image.getData()[z * image.getWidth() + x] / 255.0f);

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
        offset, msh->sharedVertexData->vertexCount, Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY);
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
    entity->setMaterialName("Terrain");
    entity->setUserAny(Ogre::Any(this));

    // Create scene node.
    sceneNode = scene->createSceneNode(name);
    sceneNode->attachObject(entity);
    sceneNode->setUserAny(Ogre::Any(this));
    //*/

    // Create entity.
    entity = scene->createEntity(name, Ogre::SceneManager::PT_PLANE);
    entity->setMaterialName("Examples/GrassFloor");
    entity->setUserAny(Ogre::Any(this));

    // Create scene node.
    sceneNode = scene->createSceneNode(name);
    sceneNode->attachObject(entity);
    sceneNode->setUserAny(Ogre::Any(this));
    sceneNode->setPosition(Ogre::Vector3(50.0f, 0.0f, 50.0f));
    sceneNode->setDirection(Ogre::Vector3::NEGATIVE_UNIT_Y);
    sceneNode->setScale(Ogre::Vector3::UNIT_SCALE * 0.5f);
}

void Terrain::unload()
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

float Terrain::getHeight(size_t x, size_t z, int offset) const
{
    static bool loaded = false;
    static Ogre::Image image;

    if (loaded == false)
    {
        image.load("terrain.png", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

        loaded = true;
    }

    return image.getData()[z * image.getWidth() + x + offset] * 1.0f;
}
