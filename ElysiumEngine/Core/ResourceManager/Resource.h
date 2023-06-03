#pragma once
#include <string>

namespace Core {

    class Resource {
	public:
		explicit Resource(const std::string& filePath)
			: m_filePath(filePath) {}

        const std::string& GetFilePath() const {
			return m_filePath;
		}


	private:
		std::string m_filePath;
	};

}
