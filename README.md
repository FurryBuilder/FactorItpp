FactorIt++
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
| Templated resolving   | &#x2713; |    1     |
| Service keys          | &#x2713; | &#x2713; |
| Decorators            | &#x2713; |          |
| Notifications         | &#x2713; |          |
| Child containers      | &#x2713; |          |
| Resolving scope       | &#x2713; |          |
| Auto cleanup          | &#x2713; |    2     |

1. Partially supported. Missing query API: `CanResolve` and `ResolveOrDefault`.
2. Partially supported. Service destructor will be called when shared_ptr dies.
