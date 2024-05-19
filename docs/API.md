# CSE_CircularBuffer Library API Reference

Version 0.0.2, +05:30 09:00:52 PM 19-05-2024, Sunday

## Index

- [CSE\_CircularBuffer Library API Reference](#cse_circularbuffer-library-api-reference)
  - [Index](#index)
  - [Classes](#classes)
  - [Class `CSE_CircularBuffer`](#class-cse_circularbuffer)
    - [`CSE_CircularBuffer()`](#cse_circularbuffer)
    - [`~CSE_CircularBuffer()`](#cse_circularbuffer-1)
    - [`getHead()`](#gethead)
    - [`getTail()`](#gettail)
    - [`getCapacity()`](#getcapacity)
    - [`isFull()`](#isfull)
    - [`isEmpty()`](#isempty)
    - [`getOccupiedLength()`](#getoccupiedlength)
    - [`getVacantLength()`](#getvacantlength)
    - [`push()`](#push)
    - [`pop()`](#pop)
    - [`bufferCopy()`](#buffercopy)
    - [`clear()`](#clear)
    - [`peek()`](#peek)


## Classes

* `CSE_CircularBuffer` - The main class for wrapping the data and functions of the library.

## Class `CSE_CircularBuffer`

### `CSE_CircularBuffer()`

This constructor creates a new `CSE_CircularBuffer` object. The array for this object can be dynamically allocated or passed as a parameter. There are two overloads. An example object `cbuffer` will be used throughout the documentation. Since this is a templated class, the user must also pass a data type.

#### Syntax 1

```cpp
CSE_CircularBuffer <CSE_CB_t> cbuffer (int length);
```

##### Parameters

- `CSE_CB_t` : A valid data type. eg. `int` or `float`.
- `int length` : The number of data items you need in the buffer.

##### Returns

`CSE_CircularBuffer` object.

#### Syntax 2

```cpp
CSE_CircularBuffer <CSE_CB_t> cbuffer (CSE_CB_t* buffer, int length);
```

##### Parameters

- `CSE_CB_t` : A valid data type. eg. `int` or `float`.
- `CSE_CB_t* buffer` : A pointer to an array of `CSE_CB_t` objects.
- `int length` : The number of data items you need in the buffer.

##### Returns

- `CSE_CircularBuffer` object.

### `~CSE_CircularBuffer()`

Destroys the `CSE_CircularBuffer` object. If memory is allocated for the buffer, it will be freed.

#### Syntax

```cpp
cbuffer.~CSE_CircularBuffer();
```

##### Parameters

None

##### Returns

None

### `getHead()`

Returns the index of the head of the buffer.

#### Syntax

```cpp
int head = cbuffer.getHead();
```

##### Parameters

None

##### Returns

- `int` : The index of the head of the buffer.

### `getTail()`

Returns the index of the tail of the buffer.

#### Syntax

```cpp
int tail = cbuffer.getTail();
```

##### Parameters

None

##### Returns

- `int` : The index of the tail of the buffer.

### `getCapacity()`

Returns the capacity of the buffer which indicates the total number of data items that can be stored in the buffer.

#### Syntax

```cpp
int capacity = cbuffer.getCapacity();
```

##### Parameters

None

##### Returns

- `int` : The capacity of the buffer.

### `isFull()`

Checks if the buffer is full.

#### Syntax

```cpp
bool full = cbuffer.isFull();
```

##### Parameters

None

##### Returns

- `bool` : `true` if the buffer is full, `false` otherwise.

### `isEmpty()`

Checks if the buffer is empty.

#### Syntax

```cpp
bool empty = cbuffer.isEmpty();
```

##### Parameters

None

##### Returns

- `bool` : `true` if the buffer is empty, `false` otherwise.

### `getOccupiedLength()`

Returns the number of occupied data items in the buffer.

#### Syntax

```cpp
int occupied = cbuffer.getOccupiedLength();
```

##### Parameters

None

##### Returns

- `int` : The number of occupied data items in the buffer.

### `getVacantLength()`

Returns the number of vacant data items in the buffer.

#### Syntax

```cpp
int vacant = cbuffer.getVacantLength();
```

##### Parameters

None

##### Returns

- `int` : The number of vacant data items in the buffer.

### `push()`

Pushes a new data item into the buffer. The data is pushed to `head` end of the buffer. There are two overloads. You can either push a single data or push an array of data. You can also specify the order of the data in the array.

#### Syntax 1

```cpp
cbuffer.push (CSE_CB_t data);
```

##### Parameters

- `CSE_CB_t data` : Data of type `CSE_CB_t`. If your data type is an `int`, for example, then the data passed should be an `int`.

##### Returns

- `int` : `0` if successful, `-1` otherwise.

#### Syntax 2

```cpp
cbuffer.push (CSE_CB_t* data, int length, int dataOrder);
```

##### Parameters

- `CSE_CB_t* data` : A pointer to an array of `CSE_CB_t` data.
- `int length` : The number of data items in the array.
- `int dataOrder` : The order of the data in the buffer. `0` for same order, `1` for reverse order. Default value is `0`.

##### Returns

- `int` : `0` if successful, `-1` otherwise.

### `pop()`

Pops one or more data items from the buffer. The data is popped from the `tail` end of the buffer. There are two overloads. You can either pop a single data or pop an array of data. You can also specify the order of the data in the array.

#### Syntax 1

```cpp
cbuffer.pop (CSE_CB_t* data);
```

##### Parameters

- `CSE_CB_t* data` : A pointer to a destination variable of `CSE_CB_t` type.

##### Returns

- `int` : `0` if successful, `-1` otherwise. The operation can fail with `-1`, if the buffer is empty.

#### Syntax 2

```cpp
cbuffer.pop (CSE_CB_t* data, int length);
```

##### Parameters

- `CSE_CB_t* data` : A pointer to a destination array of `CSE_CB_t` type.
- `int length` : The number of data items to pop. The destination array must be large enough to hold `length` data items.

##### Returns

- `int` : Number of data popped, if successful, `-1` otherwise. The operation can fail with `-1`, if the buffer is empty. If there is not enough data in the buffer, the function returns the number of data popped before the buffer became empty.

### `bufferCopy()`

This copies the data from the circular buffer to a linear buffer specified by the user. This operation doesn't pop the data from the circular buffer. The target buffer must have enough space to hold the data. The `length` is optional and if set to `0`, the entire circular buffer is copied up to `maxlen`. If the data in the circular buffer is less than `maxlen`, then the empty data is set to `0` in the target buffer. `dataOrder` is also optional and determines the order of the data in the target buffer. If set to `0`, the data is copied in the same order as in the circular buffer. If set to `1`, the data is copied in reverse order. This function returns the number of data items copied (excluding the empty data).

#### Syntax

```cpp
int bufferCopy (CSE_CB_t* data, int length, int dataOrder);
```

##### Parameters

- `CSE_CB_t* data` : A pointer to a destination array of `CSE_CB_t` type.
- `int length` : The number of data items to copy. The destination array must be large enough to hold `length` data items.
- `int dataOrder` : The order of the data in the target buffer. `0` for same order, `1` for reverse order. Default value is `0`.

##### Returns

- `int` : Number of data copied, if successful, `-1` otherwise.

### `clear()`

Clears the buffer by setting the `head` and `tail` to `0`. This operation does not clear the data in the memory.

#### Syntax

```cpp
cbuffer.clear();
```

##### Parameters

None

##### Returns

- `int` : The number of data present in the buffer before clearing.

### `peek()`

Peeks the buffer by reading a single data without popping it from the buffer.

#### Syntax

```cpp
cbuffer.peek (CSE_CB_t* data);
```

##### Parameters

- `CSE_CB_t* data` : A pointer to a destination variable of `CSE_CB_t` type.

##### Returns

- `int` : `0` if successful, `-1` otherwise.

