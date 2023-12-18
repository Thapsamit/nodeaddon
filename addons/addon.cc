// hello.cc
#include <node.h>

namespace demo
{

    using v8::FunctionCallbackInfo;
    using v8::Isolate;
    using v8::Local;
    using v8::Object;
    using v8::String;
    using v8::Value;

    void Method(const FunctionCallbackInfo<Value> &args)
    {
        Isolate *isolate = args.GetIsolate();

        // Check if the first argument is provided and is a number
        if (args.Length() < 1 || !args[0]->IsNumber())
        {
            isolate->ThrowException(
                v8::Exception::TypeError(
                    String::NewFromUtf8(isolate, "Invalid argument. Expected a number.")
                        .ToLocalChecked()));
            return;
        }

        // Extract the value of n from the first argument
        int n = args[0]->Int32Value(isolate->GetCurrentContext()).ToChecked();

        // Check if n is a positive integer
        if (n <= 0)
        {
            isolate->ThrowException(
                v8::Exception::RangeError(
                    String::NewFromUtf8(isolate, "Invalid argument. n should be a positive integer.")
                        .ToLocalChecked()));
            return;
        }

        // Create an array to store the numbers
        Local<v8::Array> resultArray = v8::Array::New(isolate, n);

        // Populate the array with numbers from 1 to n
        for (int i = 0; i < n; ++i)
        {
            resultArray->Set(isolate->GetCurrentContext(), i, v8::Integer::New(isolate, i + 1));
        }

        // Set the result to the array
        args.GetReturnValue().Set(resultArray);
    }

    void Initialize(Local<Object> exports)
    {
        NODE_SET_METHOD(exports, "hello", Method);
    }

    NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize)

} // namespace demo
