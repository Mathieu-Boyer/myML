#include "Tensor.hpp"

std::vector<size_t> flatIndexToShapeIndex(size_t flat, const std::vector<size_t> &shape){
    std::vector<size_t> shapeIndex;
    shapeIndex.resize(shape.size());

    for (int i = shape.size() - 1; i >= 0; i--){
        shapeIndex[i] = flat % shape[i];
        flat /= shape[i];
    }

    return shapeIndex;
}

size_t ndimIndexFlatIndex(const std::vector<size_t> &ndimIndex, const std::vector<size_t> &strides){
    size_t flatIndex = 0;

    for (size_t i = 0; i < ndimIndex.size(); i++)
        flatIndex += ndimIndex[i] * strides[i];
    return flatIndex;
}




Tensor Tensor::vector(size_t size, float fill){
    return Tensor({size}, fill);
}
Tensor Tensor::matrix(size_t rows, size_t columns, float fill){
    return Tensor({rows, columns}, fill);
}
Tensor Tensor::zeros(const std::vector<size_t>& shape){
    return Tensor(shape, 0);
}
Tensor Tensor::ones(const std::vector<size_t>& shape){
    return Tensor(shape, 1);
}
Tensor Tensor::identity(size_t size){
    Tensor identity({size, size}, 0);

    for (size_t i = 0; i < size; i++)
        identity(i,i) = 1;
    return identity;
}
Tensor Tensor::random_uniform(const std::vector<size_t>& shape, float min , float max, unsigned int seed) {
    std::vector<float> data;
    size_t total = Tensor().shapeProduct(shape);

    std::mt19937 gen(seed ? seed : std::random_device{}());
    std::uniform_real_distribution<float> dist(min, max);

    data.resize(total);
    for (size_t i = 0; i < total; ++i) {
        data[i] = dist(gen);
    }

    return Tensor(shape, data);
}

Tensor Tensor::random_normal(const std::vector<size_t>& shape, float mean, float std, unsigned int seed) {
    std::vector<float> data;
    size_t total = Tensor().shapeProduct(shape);

    std::mt19937 gen(seed ? seed : std::random_device{}());
    std::normal_distribution<float> dist(mean, std);

    data.resize(total);
    for (size_t i = 0; i < total; ++i) {
        data[i] = dist(gen);
    }

    return Tensor(shape, data);
}


Tensor::Tensor() : _data({}), _shape({}), _strides({}){}

Tensor::Tensor(std::vector<size_t> shape) : _shape(shape){
    resizeData();
    computeStrides();
}

Tensor::Tensor(std::vector<size_t> shape, float value) : _shape(shape){
    resizeData();
    computeStrides();
    fill(value);
}
Tensor::Tensor(std::vector<size_t> shape, const std::vector<float> &data) : _shape(shape){
    if (shapeProduct() != data.size())
        throw std::logic_error("Inconsistant data for a tensor of this shape.");
    _data = data;
    computeStrides();
}

void Tensor::computeStrides(){
    _strides.resize(_shape.size());
    if (_shape.empty())
        return;

    _strides[_shape.size() - 1] = 1;

    for (int i = (int)_shape.size() - 2; i >= 0; --i) {
        _strides[i] = _strides[i + 1] * _shape[i + 1];
    }
}

void Tensor::resizeData(){
    _data.resize(shapeProduct());
}

void Tensor::fill(float value){
    for (auto &element : _data)
        element = value;
}

size_t Tensor::shapeProduct() const{
    size_t totalElements = 1;
    for (auto &s : _shape)
        totalElements *= s;
    return totalElements;
}

size_t Tensor::shapeProduct(const std::vector<size_t>&shape) const{
    size_t totalElements = 1;
    for (auto &s : shape)
        totalElements *= s;
    return totalElements;
}

size_t Tensor::stridesProduct() const{
    size_t totalElements = 1;
    for (auto &s : _strides)
        totalElements *= s;
    return totalElements;
}


void printSpaces(size_t num){
    for (size_t i = 0 ; i< num; i ++)
        std::cout << " ";
}

void Tensor::print(size_t nest, size_t index) const{
    if (nest == _shape.size()) {
        std::cout << _data[index] << " ";
        return;
    }

    if (nest != _shape.size() - 1){
        std::cout << "\n";
        printSpaces(nest);
    }
    std::cout << "[";
    for (size_t i = 0; i < _shape[nest]; ++i) {
        size_t new_index = index + i * _strides[nest];
        print(nest + 1, new_index);
    }

    nest != _shape.size() - 1 ? (printSpaces(nest), std::cout << "],\n") : ( std::cout << "]");
}


size_t Tensor::ndim() const{
    return _shape.size();
}

void Tensor::print() const{
    std::cout << "Shape : [ ";
    for (auto &s : _shape)
        std::cout << s << " ";
    std::cout << "]\n";

    std::cout << "Strides : [ ";
    for (auto &s : _strides)
        std::cout << s << " ";
    std::cout << "]\n";

    print(0,0);
}

bool Tensor::isVector() const{
    return _shape.size() == 1;
}

bool Tensor::isMatrix() const{
    return _shape.size() == 2;
}

float &Tensor::operator()(const size_t index){
    if (index >= _data.size())
        throw std::logic_error("Index provided is out of range.");
    return(_data[index]);
}
float Tensor::operator()(const size_t index) const{
    if (index >= _data.size())
        throw std::logic_error("Index provided is out of range.");
    return(_data[index]);
}

float &Tensor::operator()(size_t rows, size_t columns){
    if (!this->isMatrix())
        throw std::logic_error("Current tensor is not a matrix.");
    if (rows >= this->_shape[0])
        throw std::logic_error("Row provided is out of range.");
    if (columns >= this->_shape[1])
        throw std::logic_error("Column provided is out of range.");
    return(_data[rows * _strides[0] + columns]);
}
float Tensor::operator()(size_t rows, size_t columns) const{
    if (!this->isMatrix())
        throw std::logic_error("Current tensor is not a matrix.");
    if (rows >= this->_shape[0])
        throw std::logic_error("Row provided is out of range.");
    if (columns >= this->_shape[1])
        throw std::logic_error("Column provided is out of range.");
    return(_data[rows * _strides[0] + columns]);
}

bool Tensor::indicesOutOfBound(const std::vector<size_t> &indices) const{
    for (size_t i = 0; i < indices.size(); i++){
        if (indices[i] >= _shape[i]){
            return true;
        }

    }
    return false;
}

Tensor Tensor::broadCast(const Tensor &main, const Tensor &broadCasted) const {
    if (main.shape().size() != broadCasted.shape().size())
        throw std::logic_error("Tensor cannot be broadcasted.");

    const auto &mainShape = main.shape();
    const auto &bShape = broadCasted.shape();
    std::vector<size_t> newShape(mainShape.size());
    for (size_t i = 0; i < newShape.size(); ++i) {
        if (mainShape[i] != bShape[i] && bShape[i] != 1)
            throw std::logic_error("Broadcasting dimensions incompatible.");
        newShape[i] = mainShape[i];
    }
    Tensor result(newShape);
    for (size_t i = 0; i < result.size(); ++i) {
        auto idx = flatIndexToShapeIndex(i, newShape);
        auto idxB = idx;

        for (size_t d = 0; d < newShape.size(); ++d)
            if (bShape[d] == 1)
                idxB[d] = 0;

        size_t flatB = ndimIndexFlatIndex(idxB, broadCasted._strides);
        result(i) = broadCasted(flatB);
    }

    return result;
}

float &Tensor::operator()(std::vector<size_t> indices){

    if (indicesOutOfBound(indices))
        throw std::logic_error("provided is out of range.");

    size_t index = 0;
    for (size_t i = 0; i < indices.size(); i++)
        index += indices[i] * _strides[i];
    return(_data[index]);
}

float Tensor::operator()(std::vector<size_t> indices) const{

    if (indicesOutOfBound(indices))
        throw std::logic_error("provided is out of range.");

    size_t index = 0;
    for (size_t i = 0; i < indices.size(); i++)
        index += indices[i] * _strides[i];
    return(_data[index]);
}

Tensor Tensor::operator+(const Tensor &rhs) const{
    if (this->_shape != rhs._shape){
        Tensor b_broadcasted = broadCast(*this, rhs);
        Tensor result(*this);
        for (size_t i = 0; i < result.size(); ++i)
            result._data[i] += b_broadcasted._data[i];
        return result;
    }

    Tensor newTensor(*this);
    for (size_t i = 0; i < newTensor._data.size(); i++)
        newTensor._data[i] += rhs._data[i];

    return newTensor;
}

Tensor &Tensor::operator+=(const Tensor &rhs) {
    if (this->_shape != rhs._shape)
        throw std::logic_error("Invalid shape for this operation.");
    for (size_t i = 0; i < _data.size(); i++)
        _data[i] += rhs._data[i];

    return *this;
}

Tensor Tensor::operator-(const Tensor &rhs) const{
    if (this->_shape != rhs._shape){
        Tensor b_broadcasted = broadCast(*this, rhs);
        Tensor result(*this);
        for (size_t i = 0; i < result.size(); ++i)
            result._data[i] -= b_broadcasted._data[i];
        return result;
    }
    Tensor newTensor(*this);

    for (size_t i = 0; i < newTensor._data.size(); i++)
        newTensor._data[i] -= rhs._data[i];

    return newTensor;
}

Tensor &Tensor::operator-=(const Tensor &rhs) {
    if (this->_shape != rhs._shape)
        throw std::logic_error("Invalid shape for this operation.");
    for (size_t i = 0; i < _data.size(); i++)
        _data[i] -= rhs._data[i];

    return *this;
}

Tensor Tensor::operator*(const Tensor &rhs) const{
    if (this->_shape != rhs._shape){
        Tensor b_broadcasted = broadCast(*this, rhs);
        Tensor result(*this);
        for (size_t i = 0; i < result.size(); ++i)
            result._data[i] *= b_broadcasted._data[i];
        return result;
    }
    Tensor newTensor(*this);

    for (size_t i = 0; i < newTensor._data.size(); i++)
        newTensor._data[i] *= rhs._data[i];

    return newTensor;
}

Tensor &Tensor::operator*=(const Tensor &rhs) {
    if (this->_shape != rhs._shape)
        throw std::logic_error("Invalid shape for this operation.");
    for (size_t i = 0; i < _data.size(); i++)
        _data[i] *= rhs._data[i];

    return *this;
}

Tensor Tensor::operator/(const Tensor &rhs) const{
    if (this->_shape != rhs._shape){
        Tensor b_broadcasted = broadCast(*this, rhs);
        Tensor result(*this);
        for (size_t i = 0; i < result.size(); ++i)
            result._data[i] /= b_broadcasted._data[i];
        return result;
    }
    Tensor newTensor(*this);

    for (size_t i = 0; i < newTensor._data.size(); i++)
        newTensor._data[i] /= (rhs._data[i] == 0)? __FLT_EPSILON__ : rhs._data[i];
    return newTensor;
}

Tensor &Tensor::operator/=(const Tensor &rhs) {
    if (this->_shape != rhs._shape)
        throw std::logic_error("Invalid shape for this operation.");
    for (size_t i = 0; i < _data.size(); i++)
        _data[i] /= (rhs._data[i] == 0)? __FLT_EPSILON__ : rhs._data[i];

    return *this;
}

Tensor Tensor::operator+(const float &rhs) const{
    Tensor newTensor(*this);

    for (size_t i = 0; i < newTensor._data.size(); i++)
        newTensor._data[i] += rhs;

    return newTensor;
}

Tensor &Tensor::operator+=(const float &rhs) {
    for (size_t i = 0; i < _data.size(); i++)
        _data[i] += rhs;

    return *this;
}

Tensor Tensor::operator-(const float &rhs) const{
    Tensor newTensor(*this);

    for (size_t i = 0; i < newTensor._data.size(); i++)
        newTensor._data[i] -= rhs;

    return newTensor;
}

Tensor &Tensor::operator-=(const float &rhs) {
    for (size_t i = 0; i < _data.size(); i++)
        _data[i] -= rhs;

    return *this;
}

Tensor Tensor::operator*(const float &rhs) const{
    Tensor newTensor(*this);

    for (size_t i = 0; i < newTensor._data.size(); i++)
        newTensor._data[i] *= rhs;

    return newTensor;
}

Tensor &Tensor::operator*=(const float &rhs) {
    for (size_t i = 0; i < _data.size(); i++)
        _data[i] *= rhs;

    return *this;
}

Tensor Tensor::operator/(const float &rhs) const{
    if (rhs == 0)
        throw std::logic_error("Dividing the tensor by 0.");
    Tensor newTensor(*this);

    for (size_t i = 0; i < newTensor._data.size(); i++)
        newTensor._data[i] /= rhs;

    return newTensor;
}

Tensor &Tensor::operator/=(const float &rhs) {
    if (rhs == 0)
        throw std::logic_error("Dividing the tensor by 0.");
    for (size_t i = 0; i < _data.size(); i++)
        _data[i] /= rhs;

    return *this;
}

Tensor Tensor::getMatrixAtBatchOffset(const std::vector<size_t>& batchIndex) const {
    size_t batchOffset = 0;

    if (batchIndex.size() > 0)
        for (size_t i = 0 ; i < batchIndex.size(); i++) {
            batchOffset += batchIndex[i] * _strides[i];
        }

    // Size of the (M x K) matrix (last two dims)
    size_t matrixSize = 1;
    for (size_t i = _shape.size() - 2 ; i < _shape.size(); i++)
        matrixSize *= _shape[i];

    std::vector<float> toFillWith(_data.begin() + batchOffset, _data.begin() + batchOffset + matrixSize);
    return Tensor({_shape[_shape.size() - 2], _shape[_shape.size() - 1]}, toFillWith);
}

Tensor Tensor::matmul2D(const Tensor &rhs) const{
    const std::vector<size_t> A_matrixShape = {this->_shape[this->_shape.size() - 2], this->_shape[this->_shape.size() - 1]};
    const std::vector<size_t> B_matrixShape = {rhs._shape[rhs._shape.size() - 2], rhs._shape[rhs._shape.size() - 1]};

    if (A_matrixShape[1] != B_matrixShape[0])
        throw std::logic_error("Shapes do not match for a matrix multiplication.");

    Tensor resultMatrix = Tensor::matrix(A_matrixShape[0] , B_matrixShape[1]);

    for (size_t i = 0 ; i < A_matrixShape[0]; i++)
        for (size_t j = 0 ; j < B_matrixShape[1]; j++)
            for (size_t k = 0 ; k < A_matrixShape[1]; k++)
                resultMatrix(i,j) += (*this)(i,k) * rhs(k,j);
    return resultMatrix;
}


Tensor Tensor::matmul(const Tensor &rhs) const{
    if (this->isVector() || rhs.isVector())
        throw std::logic_error("Matmul is only allowed with at least 2D tensors, try to reshape your 1D tensor(s).");
    if (this->isMatrix() && rhs.isMatrix())
        return matmul2D(rhs);

    const std::vector<size_t> A_batch(this->_shape.begin(), this->_shape.begin() + this->_shape.size() - 2);
    const std::vector<size_t> B_batch(rhs._shape.begin(), rhs._shape.begin() + rhs._shape.size() - 2);

    std::vector<float> newTensorData; // i'll resize later with the final size only once instead of resizing at each loop pass.


    if (A_batch != B_batch)
        throw std::logic_error("Broadcasting is not implemented yet, so tensors batch have to be the same for matmul.");

    size_t batchSize = 1;
    for (auto &batchElement : A_batch)
        batchSize *= batchElement;

    for (size_t i = 0; i < batchSize ; i++){
        const std::vector<float> &matrixData = getMatrixAtBatchOffset(flatIndexToShapeIndex(i, A_batch)).matmul2D(rhs.getMatrixAtBatchOffset(flatIndexToShapeIndex(i, B_batch)))._data;
        newTensorData.insert(newTensorData.end(), matrixData.begin(), matrixData.end());
    }

    std::vector<size_t> newTensorShape = A_batch;
    newTensorShape.resize(A_batch.size() + 2);
    newTensorShape[newTensorShape.size()-2] = this->_shape[this->_shape.size() - 2];
    newTensorShape[newTensorShape.size()-1] = rhs._shape[rhs._shape.size() - 1];

    return Tensor(newTensorShape, newTensorData);
}


Tensor Tensor::transpose(const std::vector<size_t> &order) const{
    if (this->isVector())
        throw std::logic_error("Vectors can't be transposed.");
    
    if (order.empty()){
        Tensor transposed(std::vector<size_t>(_shape.rbegin(), _shape.rend()), _data);
        transposed._strides = std::vector<size_t>(_strides.rbegin(), _strides.rend());
        return transposed;
    }
    if (order.size() != _shape.size())
        throw std::logic_error("Invalid axis order.");
    std::vector<size_t> newOrder(_shape.size());
    std::vector<size_t> newStrides(_strides.size());

    newOrder.resize(_shape.size());
    for (size_t i = 0; i < order.size(); i++){
        newOrder[i] = _shape.at(order[i]);
        newStrides[i] = _strides.at(order[i]);
    }
    
    Tensor transposed(newOrder, _data);
    transposed._strides = newStrides;
    return transposed;
}

Tensor Tensor::sum(size_t axis) const {
    if (axis >= _shape.size())
        throw std::logic_error("Axis out of bounds");
    std::vector<size_t> outShape;
    for (size_t i = 0; i < _shape.size(); ++i) {
        if (i != axis)
            outShape.push_back(_shape[i]);
    }
    Tensor result(outShape);
    for (size_t flatIndex = 0; flatIndex < _data.size(); ++flatIndex) {
        std::vector<size_t> fullIndex = flatIndexToShapeIndex(flatIndex, _shape);
        std::vector<size_t> reducedIndex;
        for (size_t i = 0; i < fullIndex.size(); ++i)
            if (i != axis)
                reducedIndex.push_back(fullIndex[i]);

        result(reducedIndex) += _data[flatIndex];
    }
    return result;
}

float Tensor::sumFloat() const {
    float sum = 0;
    for (auto &element : _data)
        sum += element;
    return sum;
}

float Tensor::meanFloat() const {
    return sumFloat() / _data.size();
}


Tensor Tensor::sum() const {
    float sum = 0;
    for (auto &element : _data)
        sum += element;
    return Tensor({1}, sum);
}

Tensor Tensor::mean() const {
    return Tensor({1}, sumFloat() / _data.size());
}

Tensor Tensor::mean(size_t axis) const{
    return sum(axis) / _shape[axis];
}

Tensor Tensor::reshape(const std::vector<size_t> &newShape) const {
    if (shapeProduct() != shapeProduct(newShape))
        throw std::logic_error("Invalid new shape.");

    return (Tensor(newShape, _data));
}


Tensor Tensor::log() const {
    Tensor outTensor(*this);
    for (size_t i = 0; i < _data.size(); i++){
        outTensor._data[i] = std::log(std::max(_data[i], __FLT_EPSILON__));
    }
    return outTensor;
}

Tensor Tensor::exp() const {
    Tensor outTensor(*this);
    for (size_t i = 0; i < _data.size(); i++){
        outTensor._data[i] = std::exp(_data[i]);
    }
    return outTensor;
}

Tensor Tensor::abs() const {
    Tensor outTensor(*this);
    for (size_t i = 0; i < _data.size(); i++){
        outTensor._data[i] = std::abs(_data[i]);
    }
    return outTensor;
}

size_t Tensor::size() const{
    return _data.size();
}

const std::vector<size_t> &Tensor::shape() const{
    return _shape;
}