#pragma once

#include <SMOG/SMOG.h>
#include <SMOG/ShaderProgram.h>
#include <SMOG/TextureFile.h>

#include <map>
#include <memory>


SMOG_NAMESPACE_ENTER
{
	template<typename T>
	struct TypedMaterialValue;
	
	struct SMOGAPI MaterialValue
	{
		enum Type
		{
			kInvalid = 0,
			kFloat,
			kRGB,
			kTexture
		};

		static std::string typeName(Type type);

		virtual ~MaterialValue() { }

		virtual Type type() const = 0;

		template<typename U>
		TypedMaterialValue<U>* as()
		{
			return dynamic_cast<TypedMaterialValue<U>*>(this);
		}

		template<typename U>
		const TypedMaterialValue<U>* as() const
		{
			return dynamic_cast<const TypedMaterialValue<U>*>(this);
		}
	};

	template<typename T>
	struct SMOGAPI TypedMaterialValue : public MaterialValue
	{
		TypedMaterialValue() { }
		TypedMaterialValue(const T& value) : value(value) { }

		virtual Type type() const;

		T value;
	};

	template<typename T>
	MaterialValue::Type TypedMaterialValue<T>::type() const
	{
		return kInvalid;
	}

	template<>
	MaterialValue::Type TypedMaterialValue<float>::type() const
	{
		return kFloat;
	}

	template<>
	MaterialValue::Type TypedMaterialValue<RGB>::type() const
	{
		return kRGB;
	}

	template<>
	MaterialValue::Type TypedMaterialValue<TextureFile>::type() const
	{
		return kTexture;
	}


	class SMOGAPI Material
	{
	public:
		static Material Load(const std::string& filename);
		
		Material();

		void load(const std::string& filename);
		void save(const std::string& filename) const;

		void setVertexShader(const std::string& vertexShader);
		void setFragmentShader(const std::string& fragmentShader);

		ShaderProgram& program();
		const ShaderProgram& program() const;

		void set(const std::string& name, float value);
		void set(const std::string& name, const RGB& value);
		void set(const std::string& name, const TextureFile& texture);

		void apply() const;

	private:
		void tryCompileProgram();

		typedef std::map<std::string, std::unique_ptr<MaterialValue>> ValueMap;
		ValueMap m_valueMap;

		std::string m_vertexShader;
		std::string m_fragmentShader;
		ShaderProgram m_program;
	};
}