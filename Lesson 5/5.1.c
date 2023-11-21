#include <stdio.h>
#include <math.h>
#include <stdlib.h>

struct Point {
    double x;
    double y;
};

double lenght(struct Point p_one, struct Point p_two) {
    return sqrt(pow((p_two.x - p_one.x), 2) + pow((p_two.y - p_one.y), 2));
}

int check_three_points(struct Point p_one, struct Point p_two, struct Point p_three) {
    return ((p_two.y - p_one.y) * (p_three.x - p_two.x) == (p_three.y - p_two.y) * (p_two.x - p_one.x));
}

int check_point_of_triangle(struct Point p_one, struct Point p_two, struct Point p_three, struct Point p_four) {
    return (((p_four.x - p_one.x) * (p_one.y - p_two.y) - (p_four.y - p_one.y) * (p_one.x - p_two.y) >= 0) &&
            ((p_four.x - p_two.x) * (p_two.y - p_three.y) - (p_four.y - p_two.y) * (p_two.x - p_three.y) >= 0) &&
            ((p_four.x - p_three.x) * (p_three.y - p_one.y) - (p_four.y - p_three.y) * (p_three.x - p_one.y)));
}

int main(int argc, char *argv[]) {
    struct Point p_one, p_two, p_three, p_four;

    p_one.x = atof(argv[1]);
    p_one.y = atof(argv[2]);

    p_two.x = atof(argv[3]);
    p_two.y = atof(argv[4]);

    p_three.x = atof(argv[5]);
    p_three.y = atof(argv[6]);

    p_four.x = atof(argv[7]);
    p_four.y = atof(argv[8]);

    double length = lenght(p_one, p_two);
    printf("Длина отрезка между точками: %f\n", length);

    int check = check_three_points(p_one, p_two, p_three);
    if (check == 1) {
        printf("Точки лежат на одной прямой\n");
    } else {
        printf("Точки не лежат на одной прямой\n");
    }

    int triangle = check_point_of_triangle(p_one, p_two, p_three, p_four);
    if (triangle == 1) {
        printf("Точка лежит внутри треугольника\n");
    } else {
        printf("Точка не лежит внутри треугольника\n");
    }
}
