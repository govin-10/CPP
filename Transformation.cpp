#include <iostream>
#include <vector>
#include <memory>
#include <cmath>

struct Vertex {
    double x;
    double y;
    double z;

    Vertex(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {}
};

class Box {
private:
    std::vector<Vertex> vertices;

public:
    Box(const std::vector<Vertex>& vertices_) : vertices(vertices_) {}

    const std::vector<Vertex>& getVertices() const {
        return vertices;
    }

    void setVertices(const std::vector<Vertex>& vertices_) {
        vertices = vertices_;
    }
};

class Transformation {
public:
    static std::shared_ptr<Box> rotateAboutX(std::shared_ptr<Box> box, double angle_x) {
        std::vector<Vertex> vertices = box->getVertices();
        double rad = angle_x * M_PI / 180.0;

        for (auto& vertex : vertices) {
            double y = vertex.y * cos(rad) - vertex.z * sin(rad);
            double z = vertex.y * sin(rad) + vertex.z * cos(rad);
            vertex.y = y;
            vertex.z = z;
        }

        box->setVertices(vertices);
        return box;
    }

    static std::shared_ptr<Box> rotateAboutY(std::shared_ptr<Box> box, double angle_y) {
        std::vector<Vertex> vertices = box->getVertices();
        double rad = angle_y * M_PI / 180.0;

        for (auto& vertex : vertices) {
            double x = vertex.z * sin(rad) + vertex.x * cos(rad);
            double z = vertex.z * cos(rad) - vertex.x * sin(rad);
            vertex.x = x;
            vertex.z = z;
        }

        box->setVertices(vertices);
        return box;
    }

    static std::shared_ptr<Box> rotateAboutZ(std::shared_ptr<Box> box, double angle_z) {
        std::vector<Vertex> vertices = box->getVertices();
        double rad = angle_z * M_PI / 180.0;

        for (auto& vertex : vertices) {
            double x = vertex.x * cos(rad) - vertex.y * sin(rad);
            double y = vertex.x * sin(rad) + vertex.y * cos(rad);
            vertex.x = x;
            vertex.y = y;
        }

        box->setVertices(vertices);
        return box;
    }

    static std::shared_ptr<Box> scale(std::shared_ptr<Box> box, double scale_factor) {
        std::vector<Vertex> vertices = box->getVertices();

        for (auto& vertex : vertices) {
            vertex.x *= scale_factor;
            vertex.y *= scale_factor;
            vertex.z *= scale_factor;
        }

        box->setVertices(vertices);
        return box;
    }
};

int main() {
    std::vector<Vertex> vertices = {
        Vertex(0, 0, 0), Vertex(1, 0, 0), Vertex(1, 1, 0), Vertex(0, 1, 0),
        Vertex(0, 0, 1), Vertex(1, 0, 1), Vertex(1, 1, 1), Vertex(0, 1, 1)
    };

    std::shared_ptr<Box> box = std::make_shared<Box>(vertices);

    //Implementation
    box = Transformation::rotateAboutX(box, 45);
    box = Transformation::rotateAboutY(box, 30);
    box = Transformation::rotateAboutZ(box, 60);
    box = Transformation::scale(box, 2.0);

    const std::vector<Vertex>& transformedVertices = box->getVertices();
    for (const auto& vertex : transformedVertices) {
        std::cout << "(" << vertex.x << ", " << vertex.y << ", " << vertex.z << ")\n";
    }

    return 0;
}
