FactorIt++ [![Build Status](https://travis-ci.org/FurryBuilder/FactorItpp.svg?branch=master)](https://travis-ci.org/FurryBuilder/FactorItpp)
==========

This is a port of the FactorIt .NET dependency injection container to C++. This port is designed to behave and feel just like the original. It uses the same fluent interface as the .NET version and strive to offer a similar feature set.

Take a look at the [FactorIt repository](https://github.com/FurryBuilder/FactorIt) to get a better idea of where this is going.

Feature Compatibility List
--------------------------

| Feature               |   .NET   |    C++   |
| --------------------- |:--------:|:--------:|
| No magic              | &#x2713; | &#x2713; |
| Fluent interface      | &#x2713; | &#x2713; |
| Read-only interface   | &#x2713; | &#x2713; |
| Write-only interface  | &#x2713; | &#x2713; |
| Templated binding     | &#x2713; | &#x2713; |
| Templated unbinding   |          | &#x2713; |
| Templated resolving   | &#x2713; | &#x2713; |
| Service keys          | &#x2713; | &#x2713; |
| Decorators            | &#x2713; |          |
| Notifications         | &#x2713; |          |
| Child containers      | &#x2713; |          |
| Resolving scope       | &#x2713; |          |
| Auto cleanup          | &#x2713; |    1     |

1. Partially supported. Service destructor will be called when shared_ptr dies.

Basic Scenarios
-------------------

### Configuration
To create a root container, simply use the `CreateRoot()` static method. This ensures that root containers are clearly identified in your code.

```cpp
auto container = Container::CreateRoot();
```

Then, you can simply bind any interface to a factory using the `Bind/To` fluent syntax provided by the container.

```cpp
container
    ->Bind<IService>()
    ->To([](IServiceLocator* l) { return std::make_shared<ConcreteService>(); });
```

Since this is a little long to write, we also provide you with a really simple shortcuts for services that have a default constructor.

```cpp
container
    ->Bind<IService>()
    ->To<ConcreteService>();
```

If you need to pass the container around, you can either use the `IBindingRoot` interface for a write only container or the `IServiceLocator` interface for a read only container.

### Usage

To extract a dependency from the container, you can simply use the `Resolve` method. On the first call, this will create an instance of the bound type using the provided factory. Subsequent calls will resolve to the same instance. Resolving is a thread safe operation.

```cpp
auto aConcreteService = container->Resolve<IService>();
```

Advanced Scenarios
----------------------

### Keys
As the amount of services in the container grows, you might see the need to register the same interface multiple times but with different factories. For instance, when using Reactive Extensions, you might want to register the `scheduler_interface` interface for each type of schedulers your application requires. The `Bind` method enables you to provide an optional key parameter for those cases.

```cpp
container
    ->Bind<scheduler_interface>("background")
    ->To<new_thread>();
container
    ->Bind<scheduler_interface>("immediate")
    ->To<immediate>();
```

You can also provide a default instance, when no key is provided, or an alias by using the service locator provided as the first parameter of the factory.

```cpp
container
    ->Bind<scheduler_interface>()
    ->To([](IServiceLocator* l) { return l->Resolve<scheduler_interface>("background") });
```

### Unbinding
In some rare cases, you will want to unbind a specific service from the container. For this, you can use the `Unbind` method.

```cpp
container
    ->Unbind<scheduler_interface>("background");
```
