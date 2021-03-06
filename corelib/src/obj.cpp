#include "obj.h"
#include "thread.h"
#include <algorithm>
#include <cassert>

e8::incompat_obj_exception::incompat_obj_exception(obj_protocol expected_type,
                                                   obj_protocol actual_type)
    : m_expected_type(expected_type), m_actual_type(actual_type) {}

e8::incompat_obj_exception::~incompat_obj_exception() {}

char const *e8::incompat_obj_exception::what() const noexcept {
    return (std::string("Incompatiable obj support. Expected: ") + std::to_string(m_expected_type) +
            ", Actual: " + std::to_string(m_actual_type))
        .c_str();
}

e8::if_obj_actuator::if_obj_actuator() {}

e8::if_obj_actuator::~if_obj_actuator() {}

static e8::obj_id_t g_obj_id_counter = 101;
static e8util::mutex_t g_obj_id_counter_mutex = e8util::mutex();

static e8::obj_id_t next_obj_id() {
    e8::obj_id_t next_id;
    e8util::lock(g_obj_id_counter_mutex);
    next_id = g_obj_id_counter++;
    e8util::unlock(g_obj_id_counter_mutex);
    return next_id;
}

e8::if_obj::if_obj(std::string const &name) : if_obj(next_obj_id(), name) {}

e8::if_obj::if_obj(obj_id_t id, std::string const &name) : m_id(id), m_name(name), m_dirty(true) {}

e8::if_obj::~if_obj() {}

e8::obj_id_t e8::if_obj::id() const { return m_id; }

std::string e8::if_obj::name() const { return m_name; }

void e8::if_obj::init_blueprint(std::vector<transform_stage_name_t> const &stages) {
    assert(std::set<std::string>(stages.begin(), stages.end()).size() == stages.size());
    m_blueprint.clear();
    for (unsigned i = 0; i < stages.size(); i++) {
        m_blueprint.push_back(std::make_pair(stages[i], e8util::mat44_scale(1.0f)));
    }
}

bool e8::if_obj::update_stage(transform_stage_t const &stage) {
    std::string const &stage_name = stage.first;
    assert(std::find_if(m_blueprint.begin(), m_blueprint.end(),
                        [&stage_name](transform_stage_t const &stage) {
                            return stage.first == stage_name;
                        }) != m_blueprint.end());
    for (auto it = m_blueprint.begin(); it != m_blueprint.end(); ++it) {
        if (it->first == stage.first && it->second != stage.second) {
            it->second = stage.second;
            mark_dirty();
            return true;
        }
    }
    return false;
}

e8util::mat44 e8::if_obj::blueprint_to_transform() const {
    e8util::mat44 trans = e8util::mat44_scale(1.0f);
    for (auto it = m_blueprint.begin(); it != m_blueprint.end(); ++it) {
        trans = it->second * trans;
    }
    return trans;
}

void e8::if_obj::mark_dirty() { m_dirty = true; }
void e8::if_obj::mark_clean() { m_dirty = false; }
bool e8::if_obj::dirty() const { return m_dirty; }

bool e8::if_obj::active() const { return m_active; }
void e8::if_obj::activate() { m_active = true; }
void e8::if_obj::deactivate() { m_active = false; }

bool e8::if_obj::add_child(std::shared_ptr<if_obj> const &child) {
    auto it = m_children.find(child);
    if (it == m_children.end()) {
        m_children.insert(child);
        return true;
    } else {
        return false;
    }
}

bool e8::if_obj::remove_child(std::shared_ptr<if_obj> const &child) {
    auto it = m_children.find(child);
    if (it != m_children.end()) {
        m_children.erase(it);
        return true;
    } else {
        return false;
    }
}

std::vector<e8::if_obj *> e8::if_obj::get_children(obj_protocol const &interface_type) const {
    std::vector<e8::if_obj *> result;
    for (std::shared_ptr<if_obj> const &obj : m_children) {
        if (interface_type == obj_protocol::obj_protocol_all || obj->protocol() == interface_type) {
            result.push_back(obj.get());
        }
    }
    return result;
}

std::set<std::shared_ptr<e8::if_obj>> e8::if_obj::get_children() const { return m_children; }

e8::null_obj::null_obj() : if_obj("null") {}

e8::obj_protocol e8::null_obj::protocol() const { return obj_protocol_null; }
