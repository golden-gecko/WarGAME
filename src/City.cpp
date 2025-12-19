#include "PCH.hpp"

#include "Car.hpp"
#include "City.hpp"
#include "Industrial.hpp"
#include "Residential.hpp"
#include "Road.hpp"

void City::load()
{
    unload();

    size = Ogre::Vector3(100.0f, 0.0, 100.0f);

    // Create structures.
    Industrial* i1 = new Industrial("#1", scene);
    i1->load();
    i1->setSize(Ogre::Vector3(4.0f, 2.0f, 4.0f));
    i1->setPosition(Ogre::Vector3(10.0f, 1.0f, 10.0f));

    Industrial* i2 = new Industrial("#2", scene);
    i2->load();
    i2->setSize(Ogre::Vector3(4.0f, 2.0f, 4.0f));
    i2->setPosition(Ogre::Vector3(20.0f, 1.0f, 10.0f));

    Residential* r3 = new Residential("#3", scene);
    r3->load();
    r3->setSize(Ogre::Vector3(6.0f, 2.0f, 6.0f));
    r3->setPosition(Ogre::Vector3(10.0f, 1.0f, 30.0f));

    Residential* r4 = new Residential("#4", scene);
    r4->load();
    r4->setSize(Ogre::Vector3(6.0f, 2.0f, 6.0f));
    r4->setPosition(Ogre::Vector3(10.0f, 1.0f, 40.0f));

    Residential* r5 = new Residential("#5", scene);
    r5->load();
    r5->setSize(Ogre::Vector3(6.0f, 2.0f, 6.0f));
    r5->setPosition(Ogre::Vector3(20.0f, 1.0f, 40.0f));

    objects[i1->getName()] = i1;
    objects[i2->getName()] = i2;
    objects[r3->getName()] = r3;
    objects[r4->getName()] = r4;
    objects[r5->getName()] = r5;

    // Find nearest roads to each structure.


    // Create road graph.
    struct Vertex
    {
        int x;
        int y;
        int z;

        Vertex(int x, int y, int z) : x(x), y(y), z(z)
        {
        }
    };

    struct Edge
    {
        int a;
        int b;

        Edge(int a, int b) : a(a), b(b)
        {
        }
    };

    std::vector<Vertex> vertices;
    std::vector<Edge> edges;

    vertices.push_back(Vertex(1, 0, 1));
    vertices.push_back(Vertex(1, 0, 6));
    vertices.push_back(Vertex(3, 0, 6));
    vertices.push_back(Vertex(3, 0, 9));
    vertices.push_back(Vertex(9, 0, 6));
    vertices.push_back(Vertex(9, 0, 1));
    vertices.push_back(Vertex(1, 0, 29));

    edges.push_back(Edge(0, 1));
    edges.push_back(Edge(1, 2));
    edges.push_back(Edge(2, 3));
    edges.push_back(Edge(2, 4));
    edges.push_back(Edge(4, 5));
    edges.push_back(Edge(0, 5));
    edges.push_back(Edge(1, 6));

    // Create roads from graph.
    for (std::vector<Edge>::const_iterator i = edges.begin(); i != edges.end(); ++i)
    {
        std::stringstream name;

        name << "Road " << i->a << ":" << i->b << " (edge)";

        Vertex a = vertices[i->a];
        Vertex b = vertices[i->b];

        // Check if road is parallel to X or Z axis.
        if (Ogre::Math::Abs(b.x - a.x) > 1)
        {
            Road* road = new Road(name.str(), scene);

            road->load();
            road->setPosition(Ogre::Vector3(a.x + (b.x - a.x) * 0.5f + 0.5f, 0.01f, a.z + 0.5f));
            road->setSize(Ogre::Vector3(Ogre::Math::Abs(b.x - a.x) - 1.0f, 1.0f, 1.0f));
            road->setType(Road::X);

            objects[road->getName()] = road;
        }
        else if (Ogre::Math::Abs(b.z - a.z) > 1)
        {
            Road* road = new Road(name.str(), scene);

            road->load();
            road->setPosition(Ogre::Vector3(a.x + 0.5f, 0.01f, a.z + (b.z - a.z) * 0.5f + 0.5f));
            road->setSize(Ogre::Vector3(1.0f, 1.0f, Ogre::Math::Abs(b.z - a.z) - 1.0f));
            road->setType(Road::Z);

            objects[road->getName()] = road;
        }
    }

    for (std::vector<Vertex>::const_iterator i = vertices.begin(); i != vertices.end(); ++i)
    {
        std::stringstream name;

        name << "Road " << i->x << ":" << i->z << " (vertex)";

        Road* road = new Road(name.str(), scene);

        road->load();
        road->setPosition(Ogre::Vector3(i->x + 0.5f, 0.01f, i->z + 0.5f));
        road->setSize(Ogre::Vector3(1.0f, 1.0f, 1.0f));

        objects[road->getName()] = road;
    }

    // Create cars.
    Car* c1 = new Car("Car #1", scene);
    c1->load();
    c1->setSize(Ogre::Vector3::UNIT_SCALE * Ogre::Vector3(0.1f, 0.25f, 0.5f));
    c1->setPosition(Ogre::Vector3(1.75f, 0.01f, 2.5f));

    Car* c2 = new Car("Car #2", scene);
    c2->load();
    c2->setSize(Ogre::Vector3::UNIT_SCALE * Ogre::Vector3(0.1f, 0.25f, 0.5f));
    c2->setPosition(Ogre::Vector3(1.75f, 0.01f, 3.5f));

    Car* c3 = new Car("Car #3", scene);
    c3->load();
    c3->setSize(Ogre::Vector3::UNIT_SCALE * Ogre::Vector3(0.1f, 0.25f, 0.5f));
    c3->setPosition(Ogre::Vector3(1.75f, 0.01f, 4.5f));

    objects[c1->getName()] = c1;
    objects[c2->getName()] = c2;
    objects[c3->getName()] = c3;

    // Print some debug informations.
    for (std::map<std::string, Object*>::const_iterator i = objects.begin(); i != objects.end(); ++i)
    {
        Industrial* industrial = dynamic_cast<Industrial*>(i->second);
        Residential* residential = dynamic_cast<Residential*>(i->second);

        if (industrial)
        {
            std::cout << "Industrial: " << i->first << ": " << industrial->getWorkers() << std::endl;
        }
        else if (residential)
        {
            std::cout << "Residential: " << i->first << ": " << residential->getResidents() << std::endl;
        }
    }
}

void City::unload()
{
    for (std::map<std::string, Object*>::iterator i = objects.begin(); i != objects.end(); ++i)
    {
        i->second->unload();

        delete i->second;
    }
}

void City::update(float time)
{
    for (std::map<std::string, Object*>::iterator i = objects.begin(); i != objects.end(); ++i)
    {
        i->second->update(time);
    }
}
