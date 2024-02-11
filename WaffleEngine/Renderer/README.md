
// Function to load a texture from a file
unsigned int LoadTexture(const char* path) {
    int width, height, channels;
    unsigned char* data = stbi_load(path, &width, &height, &channels, 0);
    if (!data) {
        std::cerr << "Failed to load texture from file: " << path << std::endl;
        return 0;
    }

    unsigned int texture;
    glGenTextures(1, &texture)
    glBindTexture(GL_TEXTURE_2D, texture)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR)
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data)
    glGenerateMipmap(GL_TEXTURE_2D)
    glBindTexture(GL_TEXTURE_2D, 0)
    stbi_image_free(data);
    return texture;
}

// Function to create a shader
unsigned int CreateShader(const char* vertexShaderSource, const char* fragmentShaderSource) {
    unsigned int program = glCreateProgram();
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr)
    glCompileShader(vertexShader)
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success)
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog)
        std::cerr << "Failed to compile vertex shader: " << infoLog << std::endl;
    }
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr)
    glCompileShader(fragmentShader)
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success)
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog)
        std::cerr << "Failed to compile fragment shader: " << infoLog << std::endl;
    }
    glAttachShader(program, vertexShader)
    glAttachShader(program, fragmentShader)
    glLinkProgram(program)
    glGetProgramiv(program, GL_LINK_STATUS, &success)
    if (!success) {
        glGetProgramInfoLog(program, 512, nullptr, infoLog)
        std::cerr << "Failed to link program: " << infoLog << std::endl;
    }
    glDeleteShader(vertexShader)
    glDeleteShader(fragmentShader)
    return program;
}

// Function to create a vertex buffer object
unsigned int CreateVBO(const float* vertices, unsigned int size) {
    unsigned int vbo;
    glGenBuffers(1, &vbo)
    glBindBuffer(GL_ARRAY_BUFFER, vbo)
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW)
    return vbo;
}

// Function to create a vertex array object
unsigned int CreateVAO() {
    unsigned int vao;
    glGenVertexArrays(1, &vao)
    glBindVertexArray(vao)
    return vao;
}

// Function to create a vertex array object
void BindVAO(unsigned int vao) {
    glBindVertexArray(vao)
}

// Function to create a vertex array object
void UnbindVAO() {
    glBindVertexArray(0)
}

// Function to create a vertex array object
void BindVBO(unsigned int vbo) {
    glBindBuffer(GL_ARRAY_BUFFER, vbo)
}

// Function to create a vertex array object
void UnbindVBO() {
    glBindBuffer(GL_ARRAY_BUFFER, 0)
}

// Function to create a vertex array object
void SetVertexAttribPointer(unsigned int index, int size, unsigned int type, bool normalized, int stride, const void* pointer) {
    glVertexAttribPointer(index, size, type, normalized, stride, pointer)
    glEnableVertexAttribArray(index)
}

// Function to create a vertex array object
void DrawTriangles(unsigned int count) {
    glDrawArrays(GL_TRIANGLES, 0, count)
}

// Function to create a vertex array object
void DrawElements(unsigned int count) {
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr)
}

// Function to create a vertex array object
void SetUniform1i(unsigned int program, const char* name, int value) {
    glUniform1i(glGetUniformLocation(program, name), value)
}

// Function to create a vertex array object
void SetUniform4f(unsigned int program, const char* name, float v0, float v1, float v2, float v3) {
    glUniform4f(glGetUniformLocation(program, name), v0, v1, v2, v3)
}