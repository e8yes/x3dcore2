#include "testresource.h"
#include "../src/resource.h"
#include <string>

test::test_resource::test_resource() {}

test::test_resource::~test_resource() {}

void test::test_resource::run() const {
    e8util::cornell_scene scene;
    std::vector<std::shared_ptr<e8::if_obj>> roots = scene.load_roots();
    e8util::wavefront_obj wfo("test_cornellball");
    wfo.save_roots(roots);
}
