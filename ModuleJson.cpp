#include "ModuleJSON.h"
#include "Globals.h"
#include <stdio.h>
#include "imgui.h"
#include "ModuleFileSystem.h"

ModuleJSON::ModuleJSON(bool start_enabled) : Module(start_enabled)
{
	SetName("JSON");
}

ModuleJSON::~ModuleJSON()
{
}

bool ModuleJSON::Awake()
{
	bool ret = true;

	LOG_OUT("Loading JSON Module");

	return ret;
}

JSON_File* ModuleJSON::LoadJSON(const char * path)
{
	JSON_File* ret = nullptr;

	if (!App->fs->exists(path)) {
			CreateJSON(path);
		LOG_OUT("File Does not Exist");
	}
	if (App->fs->exists(path)) {
		JSON_Value *user_data = json_parse_file(path);
		JSON_Object *root_object = json_value_get_object(user_data);

		if (user_data == nullptr)
		{
			LOG_OUT("Error loading %s", path);
		}
		else
		{
			LOG_OUT("Succes loading %s", path);

			JSON_File* new_doc = new JSON_File(user_data, root_object, path);
			files.push_back(new_doc);

			ret = new_doc;
			ret->Save();
		}
	}
	return ret;
}


JSON_File* ModuleJSON::CreateJSON(const char * path)
{
	JSON_File* ret = nullptr;

	if (App->fs->exists(path))
	{
		LOG_OUT("Error creating %s. There is already a file with this path/name", path);
	}
	else
	{
		JSON_Value* root_value = json_value_init_object();

		if (root_value == nullptr)
		{
			LOG_OUT("Error creating %s. Wrong path?", path);
		}
		else
		{

			JSON_Object* root_object = json_value_get_object(root_value);

			JSON_File* new_doc = new JSON_File(root_value, root_object, path);
			files.push_back(new_doc);

			ret = new_doc;
			ret->Save();
		}
	}

	return ret;
}

bool ModuleJSON::CleanUp()
{
	bool ret = true;

	LOG_OUT("Unloading JSON Module");

	for (list<JSON_File*>::iterator it = files.begin(); it != files.end();)
	{
		(*it)->CleanUp();
		delete (*it);

		it = files.erase(it);
	}

	return ret;
}

void ModuleJSON::ImGuiDraw()
{
}

JSON_File::JSON_File(JSON_Value * _value, JSON_Object * _object, const char* _path)
{
	this->val = _value;
	this->obj = _object;
	this->root = _object;
	this->path = _path;
}

JSON_File::~JSON_File()
{

}

void JSON_File::SetString(const char * name, const char * str)
{
	json_object_dotset_string(obj, name, str);
}

void JSON_File::SetBool(const char * name, bool b)
{
	json_object_dotset_boolean(obj, name, b);
}

void JSON_File::SetNumber(const char * name, double n)
{
	json_object_dotset_number(obj, name, n);
}

const char * JSON_File::GetString(const char * name)
{
	return json_object_dotget_string(obj, name);
}

const char* JSON_File::GetString(const char * name, const char * fallback)
{
	if (json_object_dothas_value_of_type(obj, name, json_value_type::JSONString))
		return json_object_dotget_string(obj, name);
	else
		return fallback;
	
}

bool JSON_File::GetBool(const char * name)
{
	return json_object_dotget_boolean(obj, name);
}

bool JSON_File::GetBool(const char * name, bool fallback)
{
	bool ret = fallback;

	if (json_object_dothas_value_of_type(obj, name, json_value_type::JSONBoolean))
		ret = json_object_dotget_boolean(obj, name);

	return ret;
}

double JSON_File::GetNumber(const char * name)
{
	return json_object_dotget_number(obj, name);
}

double JSON_File::GetNumber(const char * name, double fallback)
{
	double ret = fallback;

	if (json_object_dothas_value_of_type(obj, name, json_value_type::JSONNumber))
		ret = json_object_dotget_number(obj, name);

	return ret;
}

void JSON_File::AddArray(const char * name)
{
	JSON_Value* val = json_value_init_array();
	JSON_Array* jarr = json_value_get_array(val);

	json_object_dotset_value(obj, name, val);

}

void JSON_File::AddArraySection(const char * name)
{
	JSON_Array* jarr = json_object_get_array(obj, name);
	if (jarr != nullptr)
		json_array_append_value(jarr, json_value_init_object());
}

bool JSON_File::FindInsideArray(const char * val, int id, json_value_type type)
{
	bool ret = false;

	JSON_Array* jarr = json_object_get_array(obj, val);
	if (jarr != nullptr) {
		JSON_Value* value = json_array_get_value(jarr, id);
		if (value != nullptr && json_value_get_type(value) == type)
			ret = true;
	}


	return ret;
}

bool JSON_File::MoveInsideArray(const char * val, int id)
{
	bool ret = false;

	JSON_Array* jarr = json_object_get_array(obj, val);
	if (jarr != nullptr) {
		JSON_Object* jobj = json_array_get_object(jarr, id);
		obj = jobj;

		ret = true;
	}

	return ret;
}

bool JSON_File::MoveTo(const char * move)
{
	bool ret = false;

	JSON_Object* jobj = json_object_get_object(obj, move);

	if (jobj != nullptr) {
		obj = jobj;
		ret = true;
	}

	return ret;
}
bool JSON_File::MoveToInsideArray(const char * move, int i)
{
	bool ret = false;

	JSON_Array* jarr = json_object_get_array(obj, move);
	if (jarr != nullptr) {
		JSON_Object* jobj = json_array_get_object(jarr, i);
		obj = jobj;

		ret = true;
	}

	return ret;
}
void JSON_File::ClearArray(const char * name)
{
	JSON_Array* array = json_object_get_array(obj, name);

	if (array != nullptr)
		json_array_clear(array);
}

int JSON_File::ArraySize(const char * array)
{
	int ret = 0;

	JSON_Array* jarr = json_object_get_array(obj, array);
	if (jarr != nullptr)
		ret = json_array_get_count(jarr);

	return ret;
}

void JSON_File::ArrayAddString(const char * array, const char * str)
{
	JSON_Array* jarr = json_object_get_array(obj, array);
	if (jarr != nullptr)
		json_array_append_string(jarr, str);
}

void JSON_File::ArrayAddBool(const char * array, bool b)
{
	JSON_Array* jarr = json_object_get_array(obj, array);
	if (jarr != nullptr)
		json_array_append_boolean(jarr, b);
}

void JSON_File::ArrayAddNumber(const char * array, double num)
{
	JSON_Array* jarr = json_object_get_array(obj, array);
	if (jarr != nullptr)
		json_array_append_number(jarr, num);
}

void JSON_File::ArrayAddObject(const char * array)
{
	JSON_Array* arr = json_object_get_array(obj, array);

	if (array != nullptr)
		json_array_append_value(arr, json_value_init_object());
}


const char * JSON_File::ArrayGetString(const char * array, unsigned int index, const char * fallback)
{
	const char* ret = nullptr;
	JSON_Array* jarr = json_object_get_array(obj, array);
	if (jarr != nullptr)
		if (FindInsideArray(array, index, json_value_type::JSONString))
			ret = json_array_get_string(jarr, index);
	return ret;
}

bool JSON_File::ArrayGetBool(const char * array, unsigned int index, bool fallback)
{
	bool ret = false;
	JSON_Array* jarr = json_object_get_array(obj, array);
	if (jarr != nullptr)
		if (FindInsideArray(array, index, json_value_type::JSONBoolean))
			ret = json_array_get_boolean(jarr, index);
	return ret;
}

double JSON_File::ArrayGetNumber(const char * array, unsigned int index, double fallback)
{
	double ret = 0;
	JSON_Array* jarr = json_object_get_array(obj, array);
	if (jarr != nullptr)
		if (FindInsideArray(array, index, json_value_type::JSONNumber))
			ret = json_array_get_number(jarr, index);
	return ret;
}

void JSON_File::AddObject(const char * name)
{
	json_object_set_value(obj, name, json_value_init_object());
}

void JSON_File::RemoveObject(const char * name)
{
	json_object_remove(obj, name);
}

bool JSON_File::ChangeObject(const char * name)
{
	bool ret = false;

	JSON_Object* _obj = json_object_get_object(obj, name);

	if (obj != nullptr)
	{
		obj = _obj;
		ret = true;
	}

	return ret;
}

bool JSON_File::ChangeObjectFromArray(const char * array, unsigned int index)
{
	bool ret = false;
	JSON_Array* arr = json_object_get_array(obj, array);
	if (arr != nullptr) {
		JSON_Object* _obj = json_array_get_object(arr, index);
		if (_obj != nullptr)
		{
			ret = true;
			obj = _obj;
		}
	}
	return ret;
}

void JSON_File::RootObject()
{
	obj = root;
}

const char * JSON_File::GetPath()
{
	return path;
}

void JSON_File::Save()
{
	json_serialize_to_file_pretty(val, path);
}

void JSON_File::CleanUp()
{
	json_value_free(val);
}


